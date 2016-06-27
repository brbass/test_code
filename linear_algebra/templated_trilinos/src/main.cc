#include "mpi.h"

#include "Test_Trilinos.hh"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    
    int size = 9;
    int num_eigenvalues = 2;
    double dx = 0.1;
    double sigma_a = 1.0;
    double nu_sigma_f = 0.2;
    double q = 1.0;

    bool print = true;
    
    Test_Trilinos trilinos(size,
                           dx,
                           sigma_a,
                           nu_sigma_f,
                           q,
                           print);

    // trilinos.test_dense();
    // trilinos.test_steady();
    trilinos.test_eigenvalue(num_eigenvalues);
    
    MPI_Finalize();
}

