#include <iostream>
#include <vector>
#include <string>
#include <random>

#include <mpi.h>

#include <Epetra_MpiComm.h>
#include <Epetra_Map.h>
#include <Epetra_CrsMatrix.h>
#include <Epetra_MultiVector.h>
#include <Epetra_LinearProblem.h>
#include <Amesos.h>

using namespace std;

class amesos_test
{
    
private:
    
    const int index_base_ = 0;
    int num_global_elements_ = 0; // number of global rows
    int num_matrices_ = 0;
    int num_my_elements_ = 0; // number of local rows
    const int num_vectors_ = 1; // number of solution/source vectors
    
    vector<int> num_entries_per_row_;
    vector<int> my_global_elements_;
    
    Epetra_Map *map_ = 0;
    Epetra_MpiComm *comm_ = 0;
    vector<Epetra_CrsMatrix> matrix_;
    vector<Epetra_MultiVector> lhs_;
    vector<Epetra_MultiVector> rhs_;
    vector<Epetra_LinearProblem> problem_;
    
    default_random_engine generator_;
    uniform_real_distribution<double> distribution_;
    
    string solver_type_ = "Klu";
    
    vector<Amesos_BaseSolver*> solver_;
    Amesos factory_;
    Teuchos::ParameterList list_;

public:

    amesos_test(int num_global_elements, int num_matrices):
        num_global_elements_(num_global_elements),
        num_matrices_(num_matrices)
    {
        comm_ = new Epetra_MpiComm(MPI_COMM_WORLD);
        map_ = new Epetra_Map(num_global_elements_, index_base_, *comm_);
        
        num_my_elements_ = map_->NumMyElements();
        my_global_elements_.assign(map_->MyGlobalElements(), map_->MyGlobalElements() + num_my_elements_);
        num_entries_per_row_.resize(num_my_elements_, 0);
        
        for (unsigned i = 0; i < num_my_elements_; ++i)
        {
            unsigned j = my_global_elements_[i];

            if (j == 0 || j == num_global_elements_ - 1)
            {
                num_entries_per_row_[i] = 2;
            }
            else
            {
                num_entries_per_row_[i] = 3;
            }
        }

        list_.set("PrintTiming", true);
        list_.set("PrintStatus", true);
        
        for (unsigned m = 0; m < num_matrices_; ++m)
        {
            Epetra_CrsMatrix matrix (Copy, *map_, &num_entries_per_row_[0], true);

            for (int i = 0; i < num_my_elements_; ++i)
            {
                vector<double> values(num_entries_per_row_[i], 0);
                vector<int> indices(num_entries_per_row_[i], 0);

                int j = my_global_elements_[i];
                
                if (j == 0)
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
                        indices[k] = j - 1 + k;
                        values[k] = distribution_(generator_);
                    }
                
                }
                
                matrix.InsertGlobalValues(j, num_entries_per_row_[i], &values[0], &indices[0]);
            }
            
            matrix.FillComplete();
            
            matrix_.push_back(matrix);

            lhs_.push_back(Epetra_MultiVector(*map_, num_vectors_));
            rhs_.push_back(Epetra_MultiVector(*map_, num_vectors_));
            
            lhs_.back().PutScalar(0.0);
            rhs_.back().Random();

            problem_.push_back(Epetra_LinearProblem(&matrix_.back(), &lhs_.back(), &rhs_.back()));
            solver_.push_back(factory_.Create(solver_type_, problem_.back()));

            if (solver_.back() == NULL)
            {
                cerr << "Specified solver \"" << solver_type_ << "\" is not available." << endl;
            }
            
            solver_.back()->SetParameters(list_);
            
            solver_.back()->SymbolicFactorization();

            solver_.back()->NumericFactorization();

            solver_.back()->Solve();
        }
        for (unsigned m = 0; m < num_matrices_; ++m)
        {
            *rhs_[m][0] = 5;
            
            // cout << rhs_[m] << endl;
            // cout << lhs_[m] << endl;
        }
    }
};

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "./test [global_rows num_matrices]" << std::endl;
        return 1;
    }

    MPI_Init(&argc, &argv);
    
    unsigned n = atoi(argv[1]);
    unsigned m = atoi(argv[2]);
    
    amesos_test problem(n, m);

//    problem.solve_system();
    
//    problem.print_rhs();
//    problem.print_matrix();
//    problem.print_result();

    MPI_Finalize();
}
