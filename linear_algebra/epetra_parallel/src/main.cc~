#include <iomanip>
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>

#include <Amesos.h>
#include <AztecOO.h>
#include <AztecOO_Version.h>
#ifdef EPETRA_MPI
#  include <mpi.h>
#  include <Epetra_MpiComm.h>
#else
#  include <Epetra_SerialComm.h>
#endif
#include <Epetra_Map.h>
#include <Epetra_CrsMatrix.h>
#include <Epetra_Vector.h>
#include <Epetra_LinearProblem.h>

#include "Random_Number_Generator.hh"
#include "Timer.hh"

using namespace std;

Random_Number_Generator rng(-1, 1);

class Solver_Test
{
private:
    
    int number_of_dimensions_ = 3;
    int number_of_points_;
    int number_of_elements_;
    string solver_name_;
    vector<int> number_of_entries_per_row_;
    
    int index_base_ = 0;
    string solver_type_ = "Klu";
    Amesos factory_;
    
    int max_iterations_ = 5000;
    double tolerance_ = 1E-6;
    
    unique_ptr<Epetra_Map> map_;
#ifdef EPETRA_MPI
    unique_ptr<Epetra_MpiComm> comm_;
#else 
    unique_ptr<Epetra_SerialComm> comm_;
#endif
    
    unique_ptr<Epetra_CrsMatrix> matrix_;
    unique_ptr<Epetra_Vector> lhs_;
    unique_ptr<Epetra_Vector> rhs_;
    unique_ptr<Epetra_LinearProblem> problem_;
    unique_ptr<Amesos_BaseSolver> amesos_solver_;
    unique_ptr<AztecOO> aztec_solver_;

    void initialize_trilinos();
    int subscript_to_index(int i, int j, int k);

public:
    
    Solver_Test(int number_of_points, string solver_name);
    
    void fill_matrix();
    void solve();
    void print();
};

Solver_Test::
Solver_Test(int num,
            string solver_name):
    number_of_elements_(num*num*num),
    number_of_points_(num),
    number_of_entries_per_row_(num*num*num, 7),
    solver_name_(solver_name)
{
    initialize_trilinos();
}

void Solver_Test::
initialize_trilinos()
{
    // setup framework
#ifdef EPETRA_MPI
    comm_ = unique_ptr<Epetra_MpiComm> (new Epetra_MpiComm(MPI_COMM_WORLD));
#else
    comm_ = unique_ptr<Epetra_SerialComm> (new Epetra_SerialComm);
#endif
    map_ = unique_ptr<Epetra_Map> ( new Epetra_Map(number_of_elements_, index_base_, *comm_));
    matrix_ = unique_ptr<Epetra_CrsMatrix> (new Epetra_CrsMatrix(Copy, *map_, &number_of_entries_per_row_[0], true));
    lhs_ = unique_ptr<Epetra_Vector> (new Epetra_Vector(*map_));
    rhs_ = unique_ptr<Epetra_Vector> (new Epetra_Vector(*map_));
    
    // initialize matrix structure
    fill_matrix();
    
    // create linear problem
    problem_ = unique_ptr<Epetra_LinearProblem> (new Epetra_LinearProblem(matrix_.get(), lhs_.get(), rhs_.get()));

    if (solver_name_ == "amesos")
    {
        amesos_solver_ = unique_ptr<Amesos_BaseSolver> (factory_.Create(solver_type_, *problem_));
        amesos_solver_->SymbolicFactorization();
    }
    else
    {
        aztec_solver_ = unique_ptr<AztecOO> (new AztecOO(*problem_));
        
        aztec_solver_->SetAztecOption(AZ_precond, AZ_Jacobi);
        aztec_solver_->SetAztecOption(AZ_poly_ord, 3);
        aztec_solver_->SetAztecOption(AZ_solver, AZ_gmres);
        aztec_solver_->SetAztecOption(AZ_kspace, 1000);
        // aztec_solver_->SetAztecOption(AZ_output, AZ_none);
    }
}

int Solver_Test::
subscript_to_index(int i, int j, int k)
{
    return k + number_of_points_ * (j + number_of_points_ * i);
}

void Solver_Test::
fill_matrix()
{
    for (int i = 0; i < number_of_points_; ++i)
    {
        int im1 = i == 0 ? number_of_points_ - 1 : i - 1;
        int ip1 = i == number_of_points_ - 1 ? 0 : i + 1;

        for (int j = 0; j < number_of_points_; ++j)
        {
            int jm1 = j == 0 ? number_of_points_ - 1 : j - 1;
            int jp1 = j == number_of_points_ - 1 ? 0 : j + 1;
            
            for (int k = 0; k < number_of_points_; ++k)
            {
                int km1 = k == 0 ? number_of_points_ - 1 : k - 1;
                int kp1 = k == number_of_points_ - 1 ? 0 : k + 1;
                
                int n = subscript_to_index(i, j, k);
                int nim = subscript_to_index(im1, j, k);
                int nip = subscript_to_index(ip1, j, k);
                int njm = subscript_to_index(i, jm1, k);
                int njp = subscript_to_index(i, jp1, k);
                int nkm = subscript_to_index(i, j, km1);
                int nkp = subscript_to_index(i, j, kp1);
        
                vector<int> column_indices(number_of_entries_per_row_[n], 0);
                vector<double> fill_vector(number_of_entries_per_row_[n], 0);
        
                column_indices[0] = nim;
                column_indices[1] = njm;
                column_indices[2] = nkm;
                column_indices[3] = n;
                column_indices[4] = nkp;
                column_indices[5] = njp;
                column_indices[6] = nip;
                
                fill_vector[0] = rng.random_double();
                fill_vector[1] = rng.random_double();
                fill_vector[2] = rng.random_double();
                fill_vector[3] = rng.random_double();
                fill_vector[4] = rng.random_double();
                fill_vector[5] = rng.random_double();
                fill_vector[6] = rng.random_double();

                if (matrix_->Filled())
                {
                    matrix_->ReplaceGlobalValues(n, number_of_entries_per_row_[n], &fill_vector[0], &column_indices[0]);
                }
                else
                {
                    matrix_->InsertGlobalValues(n, number_of_entries_per_row_[n], &fill_vector[0], &column_indices[0]);
                }
                
                (*rhs_)[n] = rng.random_double();
            }
        }
    }
    
    matrix_->FillComplete();
    lhs_->PutScalar(1.0);
}

void Solver_Test::
solve()
{
    if (solver_name_ == "amesos")
    {
        amesos_solver_->NumericFactorization();
        amesos_solver_->Solve();
    }
    else
    {
        aztec_solver_->Iterate(max_iterations_, tolerance_);
    }
}

void Solver_Test::
print()
{
    cout << "*************matrix*************" << endl;
    cout << *matrix_ << endl;
    cout << "*************rhs*************" << endl;
    cout << *rhs_ << endl;
    cout << "*************lhs*************" << endl;
    cout << *lhs_ << endl;
}

int main(int argc, char* argv[])
{
#ifdef EPETRA_MPI
    MPI_Init(&argc, &argv);
#endif
    
    if (argc < 2)
    {
        cerr << "usage: main [number_of_points number_of_solves=1]" << endl;
        return 1;
    }
    
    int number_of_points = atoi(argv[1]);
    int number_of_solves = argc > 2 ? atoi(argv[2]) : 1;

    Timer timer;
    
    // create one matrix and reuse
    string solver_name = "aztec";

    timer.start();
    {
        Solver_Test test(number_of_points, solver_name);
     
        for (int i = 0; i < number_of_solves; ++i)
        {
            test.fill_matrix();
            test.solve();
            // test.print();
        }
    }
    timer.stop();
    timer.print_time();
    
    // timer.start();
    // for (int i = 0; i < number_of_solves; ++i)
    // {
    //     Solver_Test test(number_of_points, solver_name);
        
    //     test.fill_matrix();
    //     test.solve();
    // }
    // timer.stop();
    // timer.print_time();

#ifdef EPETRA_MPI
    MPI_Finalize();
#endif
}
    
