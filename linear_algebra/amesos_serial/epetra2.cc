#include <random>
#include <iostream>
#include <vector>
#include <string>

#include <Epetra_SerialDenseMatrix.h>
#include <Epetra_SerialDenseVector.h>
#include <Epetra_SerialDenseSolver.h>

using namespace std;

void epetra_solve(vector<double> &matrix, vector<double> &lhs, vector<double> &rhs, int size)
{
    Epetra_SerialDenseMatrix epetra_matrix (View, &matrix[0], size, size, size);
    Epetra_SerialDenseVector epetra_lhs (size);
    Epetra_SerialDenseVector epetra_rhs (View, &rhs[0], size);
    
    Epetra_SerialDenseSolver solver;
    
    solver.FactorWithEquilibration(true);
    solver.SetMatrix(epetra_matrix);
    solver.SetVectors(epetra_lhs, epetra_rhs);
    solver.Solve();
    
    lhs.assign(solver.X(), solver.X() + size);
    
    //cout << "epetra solution: " << lhs[0] << "   " << lhs[1] << endl;
}

void analytic_solve(vector<double> &matrix, vector<double> &lhs, vector<double> &rhs)
{
    lhs[0] = (matrix[3] * rhs[0] - matrix[1] * rhs[1]) / (matrix[0] * matrix[3] - matrix[1] * matrix[2]);
    lhs[1] = (matrix[2] * rhs[0] - matrix[0] * rhs[1]) / (matrix[1] * matrix[2] - matrix[0] * matrix[3]);
    
    //cout << "analytic solution: " << lhs[0] << "   " << lhs[1] << endl;
}

int main (int argc, char *argv[])
{
    // MPI_Init(&argc, &argv);

    unsigned iterations = 1e6;
    
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);
    
    int number_of_rows = 2;
    
    double t1, t2, t3, t4;
    vector<double> matrix(number_of_rows * number_of_rows, 0);
    vector<double> lhs(number_of_rows, 0);
    vector<double> rhs(number_of_rows, 0);
    
    // t1 = MPI_Wtime();
    
    for (unsigned t = 0; t < iterations; ++t)
    {
        for (unsigned i1 = 0; i1 < number_of_rows; ++i1)
        {
            for (unsigned i2 = 0; i2< number_of_rows; ++i2)
            {
                matrix[i2 + number_of_rows * i1] = 1.0 * t / iterations + 2 * i1  + 3 * i2;
            }
            
            rhs[i1] = i1 + t + 1;
        }
        
        analytic_solve(matrix, lhs, rhs);
    }
    
    // t2 = MPI_Wtime();
        
    // cout << t2-t1 << endl;
    
    for (unsigned t = 0; t < iterations; ++t)
    {
        for (unsigned i1 = 0; i1 < number_of_rows; ++i1)
        {
            for (unsigned i2 = 0; i2< number_of_rows; ++i2)
            {
                matrix[i1 + number_of_rows * i2] = 1.0 * t / iterations + 2 * i1  + 3 * i2;
            }
            
            rhs[i1] = i1 + t + 1;
        }
        
        epetra_solve(matrix, lhs, rhs, number_of_rows);
    }
    
    // t3 = MPI_Wtime();

    // cout << t3 - t2 << endl;
    
    // MPI_Finalize();
}
