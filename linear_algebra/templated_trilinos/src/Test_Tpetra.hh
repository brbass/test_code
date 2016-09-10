#ifndef Test_Tpetra_hh
#define Test_Tpetra_hh

#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "Amesos2.hpp"
#include "AnasaziBlockKrylovSchurSolMgr.hpp"
#include "AnasaziBasicEigenproblem.hpp"
#include "AnasaziGeneralizedDavidsonSolMgr.hpp"
#include "AnasaziLOBPCGSolMgr.hpp"
#include "AnasaziTpetraAdapter.hpp"
#include "BelosSolverFactory.hpp"
#include "BelosTpetraAdapter.hpp"
#include "Teuchos_VerboseObject.hpp"
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
typedef Tpetra::Vector<Scalar, LocalOrdinal, GlobalOrdinal, Node> Vector;

typedef Amesos2::Solver<CrsMatrix, MultiVector> AmesosSolver;

typedef Anasazi::BasicEigenproblem<Scalar, MultiVector, Operator> Eigenproblem;
// typedef Anasazi::BlockKrylovSchurSolMgr<Scalar, MultiVector, Operator> AnasaziSolverManager;
typedef Anasazi::GeneralizedDavidsonSolMgr<Scalar, MultiVector, Operator> AnasaziSolverManager;
// typedef Anasazi::LOBPCGSolMgr<Scalar, MultiVector, Operator> AnasaziSolverManager;
typedef Anasazi::Eigensolution<Scalar, MultiVector> Eigensolution;

typedef Belos::LinearProblem<Scalar, MultiVector, Operator> LinearProblem;
typedef Belos::SolverFactory<Scalar, MultiVector, Operator> BelosSolverFactory;
typedef Belos::SolverManager<Scalar, MultiVector, Operator> BelosSolverManager;

using std::shared_ptr;
using std::make_shared;
using std::shared_ptr;
using std::vector;
using std::cout;
using std::endl;
using std::setw;
using Teuchos::arcp;
using Teuchos::RCP;
using Teuchos::rcp;
using Teuchos::rcpFromRef;
using Teuchos::ArrayRCP;
using Teuchos::arrayViewFromVector;
using Teuchos::ArrayView;
using Teuchos::ParameterList;
using Teuchos::parameterList;
using Teuchos::get_shared_ptr;

class Test_Tpetra
{
public:
    
    Test_Tpetra(int size,
                double dx,
                double sigma_a,
                double nu_sigma_f,
                double q,
                bool print = true);

    void test_dense();
    void test_steady();
    void test_eigenvalue(int num_eigenvalues);
    
private:

    shared_ptr<Comm> get_comm();
    shared_ptr<Map> get_map(shared_ptr<Comm> comm);
    shared_ptr<CrsMatrix> get_diffusion_matrix(shared_ptr<Map> map);

    shared_ptr<Vector> get_rhs_steady(shared_ptr<Map> map);
    shared_ptr<LinearProblem> get_steady_problem(shared_ptr<CrsMatrix> mat,
                                                 shared_ptr<Vector> lhs,
                                                 shared_ptr<Vector> rhs);
    
    shared_ptr<CrsMatrix> get_fission_matrix(shared_ptr<Map> map);
    shared_ptr<Eigenproblem> get_eigenvalue_problem(shared_ptr<CrsMatrix> mat,
                                                    shared_ptr<CrsMatrix> fis,
                                                    shared_ptr<MultiVector> vec,
                                                    int nev);
    
    int index_base_ = 0;
    size_t size_;
    double dx_;
    double sigma_a_;
    double nu_sigma_f_;
    double q_;
    bool print_;
    
    vector<size_t> num_entries_per_row_;
};

#endif
