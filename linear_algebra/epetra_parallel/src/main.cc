#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

#include <Amesos.h>
#include <AztecOO.h>
#include <AztecOO_Version.h>
#include <mpi.h>
#include <Epetra_MpiComm.h>
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

    int index_base_ = 0;
    string solver_type_ = "Klu";
    Amesos factory_;
    
    int max_iterations_ = 5000;
    double tolerance_ = 1E-6;
    
    unique_ptr<Epetra_Map> map_;
    unique_ptr<Epetra_MpiComm> comm_;
    
    unique_ptr<Epetra_CrsMatrix> matrix_;
    unique_ptr<Epetra_Vector> lhs_;
    unique_ptr<Epetra_Vector> rhs_;
    unique_ptr<Epetra_LinearProblem> problem_;
    unique_ptr<Amesos_BaseSolver> amesos_solver_;
    unique_ptr<AztecOO> aztec_solver_;
    
    int num_my_elements_;
    vector<int> my_global_elements_;
    vector<int> num_entries_per_row_;
    
    void initialize_trilinos();
    int subscript_to_index(int i, int j, int k);
    vector<int> index_to_subscript(int n);

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
    solver_name_(solver_name)
{
    initialize_trilinos();
}

void Solver_Test::
initialize_trilinos()
{
    // setup framework
    comm_ = unique_ptr<Epetra_MpiComm> (new Epetra_MpiComm(MPI_COMM_WORLD));
    map_ = unique_ptr<Epetra_Map> ( new Epetra_Map(number_of_elements_, index_base_, *comm_));
    
    num_my_elements_ = map_->NumMyElements();
    my_global_elements_.resize(num_my_elements_);
    map_->MyGlobalElements(&my_global_elements_[0]);
    num_entries_per_row_.assign(num_my_elements_, 7);

    matrix_ = unique_ptr<Epetra_CrsMatrix> (new Epetra_CrsMatrix(Copy, *map_, &num_entries_per_row_[0], true));
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

vector<int> Solver_Test::
index_to_subscript(int index)
{
    vector<int> subscript(number_of_dimensions_);
    
    int product = 1;
    for (int i = 1; i < number_of_dimensions_; ++i)
    {
        product *= number_of_points_;
    }
    
    int sum = index;
    for (int i = 0; i < number_of_dimensions_ - 1; ++i)
    {
        subscript[i] = floor(static_cast<double>(sum) / product);
        
        sum -= product * subscript[i];
        product /= number_of_points_;
    }
    
    subscript[number_of_dimensions_ - 1] = floor(static_cast<double>(sum) / product);
    
    return subscript;
}

void Solver_Test::
fill_matrix()
{
    for (int l = 0; l < num_my_elements_; ++l)
    {
        int n = my_global_elements_[l];
        
        vector<int> indices = index_to_subscript(n);
        
        int i = indices[0];
        int j = indices[1];
        int k = indices[2];
        int im1 = i == 0 ? number_of_points_ - 1 : i - 1;
        int ip1 = i == number_of_points_ - 1 ? 0 : i + 1;
        int jm1 = j == 0 ? number_of_points_ - 1 : j - 1;
        int jp1 = j == number_of_points_ - 1 ? 0 : j + 1;
        int km1 = k == 0 ? number_of_points_ - 1 : k - 1;
        int kp1 = k == number_of_points_ - 1 ? 0 : k + 1;
        
        int nim = subscript_to_index(im1, j, k);
        int nip = subscript_to_index(ip1, j, k);
        int njm = subscript_to_index(i, jm1, k);
        int njp = subscript_to_index(i, jp1, k);
        int nkm = subscript_to_index(i, j, km1);
        int nkp = subscript_to_index(i, j, kp1);
        
        vector<int> column_indices(num_entries_per_row_[l], 0);
        vector<double> fill_vector(num_entries_per_row_[l], 0);
        
        column_indices[0] = nim;
        column_indices[1] = njm;
        column_indices[2] = nkm;
        column_indices[3] = n;
        column_indices[4] = nkp;
        column_indices[5] = njp;
        column_indices[6] = nip;
        
        // fill_vector[0] = rng.random_double();
        // fill_vector[1] = rng.random_double();
        // fill_vector[2] = rng.random_double();
        // fill_vector[3] = rng.random_double();
        // fill_vector[4] = rng.random_double();
        // fill_vector[5] = rng.random_double();
        // fill_vector[6] = rng.random_double();
        
        fill_vector[0] = -1;
        fill_vector[1] = -1;
        fill_vector[2] = -1;
        fill_vector[3] = 2;
        fill_vector[4] = 1;
        fill_vector[5] = 1;
        fill_vector[6] = 1;
        
        if (matrix_->Filled())
        {
            matrix_->ReplaceGlobalValues(n, num_entries_per_row_[l], &fill_vector[0], &column_indices[0]);
        }
        else
        {
            matrix_->InsertGlobalValues(n, num_entries_per_row_[l], &fill_vector[0], &column_indices[0]);
        }
      
        int num_entries = 1;
        vector<int> global_index = {n};
        vector<double> fill_value = {rng.random_double()};
        // vector<double> fill_value = {1};
        
        rhs_->ReplaceGlobalValues(num_entries, &fill_value[0], &global_index[0]);
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
    MPI_Init(&argc, &argv);
    
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
    
    MPI_Finalize();
}
    
