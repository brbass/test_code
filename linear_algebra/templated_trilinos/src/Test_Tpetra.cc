#include "Test_Tpetra.hh"

#include "Teuchos_RCPStdSharedPtrConversions.hpp"
#include "Teuchos_ArrayRCP.hpp"
#include "Tpetra_CrsMatrix.hpp"
#include "Tpetra_ConfigDefs.hpp"
#include "Tpetra_DefaultPlatform.hpp"
#include "Tpetra_Map.hpp"
#include "Tpetra_MultiVector.hpp"
#include "Tpetra_Operator.hpp"
#include "Tpetra_Vector.hpp"

typedef int GlobalOrdinal;
typedef int LocalOrdinal;
typedef double Scalar;
typedef Tpetra::DefaultPlatform::DefaultPlatformType::NodeType Node;

typedef Teuchos::Comm<GlobalOrdinal> Comm;
typedef Tpetra::CrsMatrix<Scalar, LocalOrdinal, GlobalOrdinal, Node> CrsMatrix;
typedef Tpetra::Map<LocalOrdinal, GlobalOrdinal, Node> Map;
typedef Teuchos::MpiComm<GlobalOrdinal> MpiComm;
typedef Tpetra::Operator<> Operator;
typedef Tpetra::MultiVector<> MultiVector;

using std::make_shared;
using std::shared_ptr;
using Teuchos::arcp;
using Teuchos::RCP;
using Teuchos::rcp;

Test_Tpetra::
Test_Tpetra(int size):
    size_(size)
{
    num_entries_per_row_->assign(size_, 3);
    (*num_entries_per_row_)[0] = 2;
    (*num_entries_per_row_)[size_ - 1] = 2;
}

void Test_Tpetra::
test1()
{
    RCP<Comm> comm = rcp(new MpiComm(MPI_COMM_WORLD));
    RCP<Map> map = rcp(new Map(size_, index_base_, comm));
    RCP<CrsMatrix> mat = rcp(new CrsMatrix(map, 3));

    // shared_ptr<Comm> comm = make_shared<MpiComm>(MPI_COMM_WORLD);
    // shared_ptr<Map> map = make_shared<Map>(size_, index_base_, rcp(comm));
    // shared_ptr<CrsMatrix> mat = make_shared<CrsMatrix>(rcp(map), 3, Tpetra::ProfileType::StaticProfile);
}
