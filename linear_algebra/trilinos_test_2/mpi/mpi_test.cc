#include <iostream>
#include <mpi.h>

int main(int argc, char **argv)
{
    using namespace std;
    
    MPI_Init(&argc, &argv);

    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    cout << rank << endl;
    
    MPI_Finalize();
    
    return 0;
}
