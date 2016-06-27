#include "mpi.h"

#include "Test_Trilinos.hh"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    
    int size = 20;
    double dx = 0.1;
    double sigma_a = 1.0;
    double q = 1.0;
    
    Test_Trilinos trilinos(size,
                           dx,
                           sigma_a,
                           q);

    trilinos.test1();
    trilinos.test2();
    
    MPI_Finalize();
}

