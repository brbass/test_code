#include "Test_Trilinos.hh"

#include <iomanip>
#include <iostream>

#include "BelosSolverFactory.hpp"
#include "BelosTpetraAdapter.hpp"
#include "Teuchos_RCPStdSharedPtrConversions.hpp"
#include "Teuchos_ArrayRCP.hpp"
#include "Teuchos_SerialDenseMatrix.hpp"
#include "Teuchos_SerialDenseVector.hpp"
#include "Teuchos_SerialDenseSolver.hpp"
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
typedef Teuchos::SerialDenseMatrix<LocalOrdinal, Scalar> SerialDenseMatrix;
typedef Teuchos::SerialDenseSolver<LocalOrdinal, Scalar> SerialDenseSolver;
typedef Teuchos::SerialDenseVector<LocalOrdinal, Scalar> SerialDenseVector;
typedef Tpetra::CrsMatrix<Scalar, LocalOrdinal, GlobalOrdinal, Node> CrsMatrix;
typedef Tpetra::Map<LocalOrdinal, GlobalOrdinal, Node> Map;
typedef Teuchos::MpiComm<GlobalOrdinal> MpiComm;
typedef Tpetra::Operator<Scalar, LocalOrdinal, GlobalOrdinal, Node> Operator;
typedef Tpetra::MultiVector<Scalar, LocalOrdinal, GlobalOrdinal, Node> MultiVector;

typedef Belos::SolverFactory<Scalar, MultiVector, Operator> SolverFactory;
typedef Belos::SolverManager<Scalar, MultiVector, Operator> SolverManager;

using std::make_shared;
using std::shared_ptr;
using std::cout;
using std::endl;
using std::setw;
using Teuchos::arcp;
using Teuchos::RCP;
using Teuchos::rcp;
using Teuchos::rcpFromRef;
using Teuchos::ArrayRCP;
using Teuchos::arrayViewFromVector;
using Teuchos::ParameterList;
using Teuchos::parameterList;
using Teuchos::get_shared_ptr;

Test_Trilinos::
Test_Trilinos(int size,
            double dx,
            double sigma_a,
            double q):
    size_(size),
    dx_(dx),
    sigma_a_(sigma_a),
    q_(q)
{
    num_entries_per_row_.assign(size_, 3);
    num_entries_per_row_[0] = 2;
    num_entries_per_row_[size_ - 1] = 2;
}

void Test_Trilinos::
test1()
{
    shared_ptr<Comm> comm = make_shared<MpiComm>(MPI_COMM_WORLD);
    shared_ptr<Map> map = make_shared<Map>(size_, index_base_, rcp(comm));
    shared_ptr<CrsMatrix> mat = make_shared<CrsMatrix>(rcp(map), arcp(rcpFromRef(num_entries_per_row_)), Tpetra::ProfileType::StaticProfile);
    shared_ptr<MultiVector> lhs = make_shared<MultiVector>(rcp(map), 1);
    shared_ptr<MultiVector> rhs = make_shared<MultiVector>(rcp(map), 1);

    double on_diagonal = 2. / (dx_ * dx_) + sigma_a_;
    double off_diagonal = 1 / (dx_ * dx_);

    for (int i = 0; i < size_; ++i)
    {
        vector<int> cols;
        vector<double> vals;

        if (i != 0)
        {
            cols.push_back(i);
            vals.push_back(-off_diagonal);
        }
        cols.push_back(i);
        vals.push_back(on_diagonal);
        if (i != size_ - 1)
        {
            cols.push_back(i);
            vals.push_back(-off_diagonal);
        }

        mat->insertGlobalValues(i, arrayViewFromVector(cols), arrayViewFromVector(vals));
        rhs->replaceGlobalValue(i, 0, q_);
    }

    shared_ptr<ParameterList> params = get_shared_ptr(parameterList());
    params->set ("Num Blocks", 40);
    params->set ("Maximum Iterations", 400);
    params->set ("Convergence Tolerance", 1.0e-8);

    shared_ptr<SolverFactory> factory = make_shared<SolverFactory>();
    shared_ptr<SolverManager> solver = get_shared_ptr(factory->create("GMRES", rcp(params)));
}

void Test_Trilinos::
test2()
{
    shared_ptr<SerialDenseMatrix> mat = make_shared<SerialDenseMatrix>(size_, size_);
    shared_ptr<SerialDenseVector> rhs = make_shared<SerialDenseVector>(size_);
    shared_ptr<SerialDenseVector> lhs = make_shared<SerialDenseVector>(size_);
    shared_ptr<SerialDenseSolver> sol = make_shared<SerialDenseSolver>();

    double on_diagonal = 2. / (dx_ * dx_) + sigma_a_;
    double off_diagonal = 1 / (dx_ * dx_);
    
    for (int i = 0; i < size_; ++i)
    {
        if (i != 0)
        {
            (*mat)(i, i - 1) = -off_diagonal;
        }
        (*mat)(i, i) = on_diagonal;
        if (i != size_ - 1)
        {
            (*mat)(i, i + 1) = - off_diagonal;
        }
        
        (*rhs)(i) = q_;
    }

    sol->setMatrix(rcp(mat));
    sol->setVectors(rcp(lhs), rcp(rhs));
    sol->factor();
    sol->solve();

    cout << endl << "Test_Trilinos: test2";
    cout << (*lhs) << endl;
}
