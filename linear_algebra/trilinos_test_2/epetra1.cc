#include <iostream>
#include <vector>
#include <string>
#include <random>

#include <mpi.h>

#include <Epetra_MpiComm.h>
#include <Epetra_Map.h>
#include <Epetra_SerialDenseMatrix.h>
#include <Epetra_FECrsMatrix.h>
#include <Epetra_Vector.h>
#include <Epetra_LinearProblem.h>
#include <Amesos.h>

using namespace std;

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    // initialize Epetra
    int number_of_rows = 5;
    
    Epetra_MpiComm comm (MPI_COMM_WORLD);
    Epetra_Map map (number_of_rows, 0, comm);

    // initialize matrix and vectors
    vector<int> num_entries_per_row (number_of_rows, 3);
    num_entries_per_row[0] = 3;
    num_entries_per_row[number_of_rows - 1] = 3;
    
    Epetra_FECrsMatrix matrix (Copy, map, &num_entries_per_row[0], true);
    Epetra_Vector lhs (map, number_of_rows);
    Epetra_Vector rhs (map, number_of_rows);
    
    // fill matrix
    Epetra_SerialDenseMatrix fill_matrix (2, 2);

    for (unsigned i1 = 0; i1 < 2; ++i1)
    {
        for (unsigned i2 = 0; i2< 2; ++i2)
        {
            fill_matrix(i1, i2) += i2 + 2 * i1 + 1;
        }
    }

    Epetra_IntSerialDenseVector fill_vector (2);

    for (unsigned i = 0; i < number_of_rows - 1; ++i)
    {
        fill_vector(0) = i;
        fill_vector(1) = i + 1;
        
        matrix.InsertGlobalValues(fill_vector, fill_matrix);
    }
    
    matrix.GlobalAssemble();

    // fill vectors
    rhs.PutScalar(1.0);

    // solve problem
    Epetra_LinearProblem problem(&matrix, &lhs, &rhs);
    
    string solver_type = "Klu";
    Amesos factory;
    Amesos_BaseSolver *solver (factory.Create(solver_type, problem));

    solver->Solve();
    
    MPI_Finalize();
}
