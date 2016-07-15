#ifndef Test_Epetra_hh
#define Test_Epetra_hh

#include <string>

#include "AnasaziBlockKrylovSchurSolMgr.hpp"
#include "AnasaziBasicEigenproblem.hpp"
#include "AnasaziGeneralizedDavidsonSolMgr.hpp"
#include "AnasaziLOBPCGSolMgr.hpp"
#include "AnasaziEpetraAdapter.hpp"
#include "Epetra_Comm.h"
#include "Epetra_CrsMatrix.h"
#include "Epetra_Map.h"
#include "Epetra_MpiComm.h"
#include "Epetra_MultiVector.h"
#include "Epetra_Operator.h"
#include "Teuchos_VerboseObject.hpp"
#include "Teuchos_RCPStdSharedPtrConversions.hpp"
#include "Teuchos_ArrayRCP.hpp"
#include "Teuchos_SerialDenseMatrix.hpp"
#include "Teuchos_SerialDenseVector.hpp"
#include "Teuchos_SerialDenseSolver.hpp"

typedef Anasazi::BasicEigenproblem<double, Epetra_MultiVector, Epetra_Operator> Anasazi_Eigenproblem;
typedef Anasazi::BlockKrylovSchurSolMgr<double, Epetra_MultiVector, Epetra_Operator> Anasazi_SolverManager;
typedef Anasazi::Eigensolution<double, Epetra_MultiVector> Anasazi_Eigensolution;

using std::shared_ptr;
using std::make_shared;
using std::shared_ptr;
using std::string;
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

class Test_Epetra
{
public:

    Test_Epetra(int size,
                double dx,
                double sigma_a,
                double nu_sigma_f,
                double q,
                bool print = true);

    // void test_dense();
    // void test_steady();
    void test_eigenvalue(int num_eigenvalues);

private:

    shared_ptr<Epetra_Comm> get_comm();
    shared_ptr<Epetra_Map> get_map(shared_ptr<Epetra_Comm> comm);
    shared_ptr<Epetra_CrsMatrix> get_diffusion_matrix(shared_ptr<Epetra_Map> map);

    // shared_ptr<Epetra_Vector> get_rhs_steady(shared_ptr<Map> map);
    // shared_ptr<Epetra_LinearProblem> get_steady_problem(shared_ptr<CrsMatrix> mat,
    //                                                     shared_ptr<Vector> lhs,
    //                                                     shared_ptr<Vector> rhs);
    
    shared_ptr<Epetra_CrsMatrix> get_fission_matrix(shared_ptr<Epetra_Map> map);
    shared_ptr<Anasazi_Eigenproblem> get_eigenvalue_problem(shared_ptr<Epetra_CrsMatrix> mat,
                                                           shared_ptr<Epetra_CrsMatrix> fis,
                                                           shared_ptr<Epetra_MultiVector> vec,
                                                           int nev);
    
    int index_base_ = 0;
    int size_;
    double dx_;
    double sigma_a_;
    double nu_sigma_f_;
    double q_;
    bool print_;
    
    vector<int> num_entries_per_row_;
};

#endif
