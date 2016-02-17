
#include <iostream>
#include <vector>
#include <string>
#include <random>

#include <mpi.h>

//#include <Epetra_config.h>
#include <Epetra_MpiComm.h>
#include <Epetra_Map.h>
#include <Epetra_CrsMatrix.h>
#include <Epetra_MultiVector.h>
#include <Epetra_LinearProblem.h>

//#include "Amesos_ConfigDefs.h"
#include <Amesos.h>

class amesos_test
{
private:
    
    // Variables
    const int index_base_ = 0;
    int num_global_elements_ = 0;
    int num_diagonals_ = 0;
    int num_off_diagonals_ = 0;
    int num_my_elements_ = 0;
    const int num_vectors_ = 1;
    
    std::vector<int> num_entries_per_row_;
    std::vector<int> my_global_elements_;
    
    Epetra_Map *map_ = 0;
    Epetra_MpiComm *comm_ = 0;
    Epetra_CrsMatrix *matrix_ = 0;
    Epetra_MultiVector *lhs_ = 0;
    Epetra_MultiVector *rhs_ = 0;
    Epetra_LinearProblem *problem_ = 0;

    std::default_random_engine generator_;
    std::uniform_real_distribution<double> distribution_;
    
    std::string solver_type_ = "Klu";
    
    Amesos_BaseSolver *solver_ = 0;
    Amesos factory_;
    Teuchos::ParameterList list_;
    
public:
    
    // Constructor
    amesos_test(int n, int m):
        num_global_elements_(n),
        num_diagonals_(m),
        num_off_diagonals_((m - 1) / 2)
    {
        comm_ = new Epetra_MpiComm(MPI_COMM_WORLD);
        map_ = new Epetra_Map(num_global_elements_, index_base_, *comm_);
        
        num_my_elements_ = map_->NumMyElements();
        my_global_elements_.assign(map_->MyGlobalElements(), map_->MyGlobalElements() + n);
        
        num_entries_per_row_.resize(num_my_elements_, 0);
        
        for (int i = 0; i < num_my_elements_; ++i)
        {
            int j = my_global_elements_[i];
            
            if (j < num_off_diagonals_)
            {
                num_entries_per_row_[i] = num_off_diagonals_ + j + 1;
            }
            else if (j >= num_global_elements_ - num_off_diagonals_)
            {
                num_entries_per_row_[i] = num_global_elements_ + num_off_diagonals_ - j;
            }
            else
            {
                num_entries_per_row_[i] = num_diagonals_;
            }
        }
        
        matrix_ = new Epetra_CrsMatrix(Copy, *map_, &num_entries_per_row_[0], true);
        
        for (int i = 0; i < num_my_elements_; ++i)
        {
            std::vector<double> values(num_entries_per_row_[i], 0);
            std::vector<int> indices(num_entries_per_row_[i], 0);

            int j = my_global_elements_[i];

            if (j < num_off_diagonals_)
            {
                for (int k = 0; k < num_entries_per_row_[i]; ++k)
                {
                    indices[k] = k;
                    values[k] = distribution_(generator_);
                }
            }
            else
            {
                for (int k = 0; k < num_entries_per_row_[i]; ++k)
                {
                    indices[k] = j - num_off_diagonals_ + k;
                    values[k] = distribution_(generator_);
                }
            }
            
            matrix_->InsertGlobalValues(j, num_entries_per_row_[i], &values[0], &indices[0]);
        }
        
        lhs_ = new Epetra_MultiVector(*map_, num_vectors_);
        rhs_ = new Epetra_MultiVector(*map_, num_vectors_);
        
        lhs_->PutScalar(0.0);
        rhs_->Random();
        
        matrix_->FillComplete();
        
        problem_ = new Epetra_LinearProblem(matrix_, lhs_, rhs_);
        
        solver_ = factory_.Create(solver_type_, *problem_);
        
        if (solver_ == NULL)
        {
            std::cerr << "Specified solver \"" << solver_type_ << "\" is not available." << std::endl;
        }
        
        list_.set("PrintTiming", true);
        list_.set("PrintStatus", true);
        
        solver_->SetParameters(list_);
    };
    
    // Methods
    void solve_system()
    {
        solver_->SymbolicFactorization();

        solver_->NumericFactorization();

        solver_->Solve();
    }
    
    // Accessors
    void print_rhs()
    {
        std::cout << *rhs_ << std::endl;
    }

    void print_result()
    {
        std::cout << *lhs_ << std::endl;
    }

    void print_matrix()
    {
        std::cout << *matrix_ << std::endl;
    }
    
    // Destructor
    ~amesos_test()
    {
        delete map_;
        delete comm_;
        delete matrix_;
        delete lhs_;
        delete rhs_;
        delete problem_;
        delete solver_;
        
        comm_ = 0;
        map_ = 0;
        matrix_ = 0;
        lhs_ = 0;
        rhs_ = 0;
        problem_ = 0;
        solver_ = 0;
    }
};

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "./test [global_rows global_diagonals]" << std::endl;
        return 1;
    }

    MPI_Init(&argc, &argv);
    
    unsigned n = std::atoi(argv[1]);
    unsigned m = std::atoi(argv[2]);
    if ((m + 1) % 2 || m < 1)
    {
        std::cout << "m is odd and > 0" << std::endl;
        return 1;
    }
    
    amesos_test problem(n, m);

    problem.solve_system();
    
//    problem.print_rhs();
//    problem.print_matrix();
//    problem.print_result();

    MPI_Finalize();
}
