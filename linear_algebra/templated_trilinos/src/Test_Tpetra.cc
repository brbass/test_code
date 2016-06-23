#include "Test_Tpetra.hh"

#include <memory>

#include "Teuchos_RCPStdSharedPtrConversions.hpp"
#include "Tpetra_CrsMatrix.hpp"
#include <Tpetra_DefaultPlatform.hpp>
#include "Tpetra_Map.hpp"
#include "Tpetra_MultiVector.hpp"
#include "Tpetra_Operator.hpp"
#include "Tpetra_Vector.hpp"

typedef int GlobalOrdinal;
typedef int LocalOrdinal;
typedef double Scalar;
typedef Tpetra::DefaultPlatform::DefaultPlatformType::NodeType Node;

typedef Teuchos::Comm<GlobalOrdinal> Comm;
typedef Tpetra::CrsMatrix<Scalar> CrsMatrix;
typedef Tpetra::Map<LocalOrdinal, GlobalOrdinal, Node> Map;
typedef Teuchos::MpiComm<GlobalOrdinal> MpiComm;
typedef Tpetra::Operator<> Operator;
typedef Tpetra::MultiVector<> MultiVector;

using std::make_shared;
using std::shared_ptr;
using Teuchos::RCP;
using Teuchos::rcp;

Test_Tpetra::
Test_Tpetra(int size):
    size_(size)
{
}

void Test_Tpetra::
test1()
{
    shared_ptr<Comm> comm = make_shared<MpiComm>(MPI_COMM_WORLD);
    RCP<Comm> comm_rcp = rcp(comm);
    // shared_ptr<Map> map = make_shared<Map>(size_, index_base_, comm_rcp);
    RCP<Map> map = rcp(new Map(size_, 0, comm_rcp));
}
