#include "mpi.h"

#include "Test_Epetra.hh"
#include "Test_Tpetra.hh"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    
    int size = 20;
    int num_eigenvalues = 1;
    double dx = 0.1;
    double sigma_a = 1.0;
    double nu_sigma_f = 0.2;
    double q = 1.0;

    bool print = true;
    
    Test_Tpetra tpetra(size,
                       dx,
                       sigma_a,
                       nu_sigma_f,
                       q,
                       print);

    // tpetra.test_dense();
    // tpetra.test_steady();
    // tpetra.test_eigenvalue(num_eigenvalues);

    Test_Epetra epetra(size,
                       dx,
                       sigma_a,
                       nu_sigma_f,
                       q,
                       print);
    
    epetra.test_eigenvalue(num_eigenvalues);
    
    MPI_Finalize();
}

