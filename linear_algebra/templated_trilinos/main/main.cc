#include "mpi.h"

#include "Test_Tpetra.hh"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int size = 4;
    
    Test_Tpetra tpetra(size);

    tpetra.test1();
    
    MPI_Finalize();
}

// #include <Tpetra_DefaultPlatform.hpp>
// #include <Tpetra_MpiPlatform.hpp>
// #include <Tpetra_Vector.hpp>
// #include <Tpetra_Version.hpp>
// #include <Teuchos_GlobalMPISession.hpp>
// #include <Teuchos_oblackholestream.hpp>

// int main (int argc, char *argv[])
// {
//     typedef Tpetra::Map<> map_type;
//     typedef Tpetra::Vector<double> vector_type;
//     typedef vector_type::global_ordinal_type global_ordinal_type;
    
//     using std::endl;
//     using Teuchos::RCP;
//     Teuchos::oblackholestream blackHole;
//     Teuchos::GlobalMPISession mpiSession (&argc, &argv, &blackHole);

//     const Tpetra::global_size_t numGlobalEntries = 5;
//     const global_ordinal_type indexBase = 0;
    
//     RCP<const Teuchos::Comm<int> > comm =
//         RCP<const Teuchos::Comm<int> >(new Teuchos::MpiComm<int>(MPI_COMM_WORLD));

//     // RCP<const map_type> contigMap =
//     //     rcp (new map_type (numGlobalEntries, indexBase, comm));
    
    
    
    
//     return 0;
// }
