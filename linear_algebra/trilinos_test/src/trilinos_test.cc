#include <random>
#include <vector>

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

    solver.FactorWithEquilibration (true);
    solver.SetMatrix(epetra_matrix);
    solver.SetVectors(epetra_lhs, epetra_rhs);
    solver.Solve();
    lhs.assign(solver.X(), solver.X() + size);
}

