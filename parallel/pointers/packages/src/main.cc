#include <mpi.h>

#if defined(ENABLE_OPENMP)
#include <omp.h>
#else
inline void omp_set_num_threads(int i) {return;}
#endif

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "AztecOO.h"
#include "AztecOO_ConditionNumber.h"
#include "Amesos.h"
#include "Epetra_MpiComm.h"
#include "Epetra_SerialComm.h"
#include "Epetra_Map.h"
#include "Epetra_CrsMatrix.h"
#include "Epetra_Vector.h"
#include "Epetra_LinearProblem.h"
#include "Ifpack.h"
#include "Ifpack2_Factory.hpp"
#include "Ifpack2_ILUT.hpp"
#include "Epetra_CrsMatrix.h"
#include "Epetra_MultiVector.h"
#include "Epetra_Vector.h"
#include "Epetra_LinearProblem.h"
    
#include "BelosSolverFactory.hpp"
#include "BelosTpetraAdapter.hpp"
#include "Teuchos_VerboseObject.hpp"
#include "Teuchos_RCPStdSharedPtrConversions.hpp"
#include "Teuchos_ArrayRCP.hpp"
// #include "Teuchos_SerialDenseMatrix.hpp"
// #include "Teuchos_SerialDenseVector.hpp"
// #include "Teuchos_SerialDenseSolver.hpp"
#include "Teuchos_DefaultSerialComm.hpp"
#include "Tpetra_CrsMatrix.hpp"
#include "Tpetra_ConfigDefs.hpp"
#include "Tpetra_DefaultPlatform.hpp"
#include "Tpetra_Map.hpp"
#include "Tpetra_MultiVector.hpp"
#include "Tpetra_Operator.hpp"
#include "Tpetra_Vector.hpp"
    
#include "Random_Number_Generator.hh"

// Standard types
typedef int GlobalOrdinal;
typedef int LocalOrdinal;
typedef double Scalar;

// Teuchos types
typedef Teuchos::Comm<GlobalOrdinal> TeuchosComm;
typedef Teuchos::SerialComm<GlobalOrdinal> TeuchosSerialComm;

// Tpetra types
typedef Tpetra::DefaultPlatform::DefaultPlatformType::NodeType TpetraNode;
typedef Tpetra::Map<LocalOrdinal, GlobalOrdinal, TpetraNode> TpetraMap;
typedef Tpetra::Operator<Scalar, LocalOrdinal, GlobalOrdinal, TpetraNode> TpetraOperator;
typedef Tpetra::MultiVector<Scalar, LocalOrdinal, GlobalOrdinal, TpetraNode> TpetraMultiVector;
typedef Tpetra::Vector<Scalar, LocalOrdinal, GlobalOrdinal, TpetraNode> TpetraVector;
typedef Tpetra::CrsMatrix<Scalar, LocalOrdinal, GlobalOrdinal, TpetraNode> TpetraCrsMatrix;
typedef Tpetra::RowMatrix<Scalar, LocalOrdinal, GlobalOrdinal, TpetraNode> TpetraRowMatrix;

// Belos types
typedef Belos::LinearProblem<Scalar, TpetraMultiVector, TpetraOperator> BelosLinearProblem;
typedef Belos::SolverFactory<Scalar, TpetraMultiVector, TpetraOperator> BelosSolverFactory;
typedef Belos::SolverManager<Scalar, TpetraMultiVector, TpetraOperator> BelosSolverManager;

// Ifpack2 types
typedef Ifpack2::Preconditioner<Scalar, LocalOrdinal, GlobalOrdinal, TpetraNode> Ifpack2Preconditioner;
typedef Ifpack2::ILUT<TpetraRowMatrix> Ifpack2ILUT;

using namespace std;

shared_ptr<Epetra_CrsMatrix> get_epetra_matrix(int seed,
                                               int num_cols,
                                               int size,
                                               shared_ptr<Epetra_Map> map)
{
    Random_Number_Generator<double> rng(-1.,
                                        1.,
                                        seed + 1);
    shared_ptr<Epetra_CrsMatrix> mat
        = make_shared<Epetra_CrsMatrix>(Copy,
                                        *map,
                                        num_cols,
                                        true);

    for (int i = 0; i < size; ++i)
    {
        int starting_index = i - num_cols / 2;
        int ending_index = i + num_cols / 2;
        int current_num = ending_index - starting_index + 1;

        while (current_num < num_cols)
        {
            ending_index += 1;
            current_num += 1;
        }
        
        while (starting_index < 0)
        {
            starting_index += 1;
            ending_index += 1;
        }
        
        while (ending_index >= size)
        {
            starting_index -= 1;
            ending_index -= 1;
        }

        if (starting_index < 0 || ending_index >= size)
        {
            cout << "indexing incorrect" << endl;
        }
        
        vector<int> indices;
        for (int j = starting_index; j <= ending_index; ++j)
        {
            indices.push_back(j);
        }
        vector<double> values = rng.vector(num_cols);

        mat->InsertGlobalValues(i,
                                num_cols,
                                &values[0],
                                &indices[0]);
    }
    mat->FillComplete();
    mat->OptimizeStorage();

    return mat;
}

shared_ptr<TpetraCrsMatrix> get_tpetra_matrix(int seed,
                                              int num_cols,
                                              int size,
                                              shared_ptr<TpetraMap> map)
{
    Random_Number_Generator<double> rng(-1.,
                                        1.,
                                        seed + 1);
    shared_ptr<TpetraCrsMatrix> mat
        = make_shared<TpetraCrsMatrix>(Teuchos::rcp(map),
                                        num_cols,
                                        Tpetra::ProfileType::StaticProfile);
    
    for (int i = 0; i < size; ++i)
    {
        int starting_index = i - num_cols / 2;
        int ending_index = i + num_cols / 2;
        int current_num = ending_index - starting_index + 1;

        while (current_num < num_cols)
        {
            ending_index += 1;
            current_num += 1;
        }
        
        while (starting_index < 0)
        {
            starting_index += 1;
            ending_index += 1;
        }
        
        while (ending_index >= size)
        {
            starting_index -= 1;
            ending_index -= 1;
        }

        if (starting_index < 0 || ending_index >= size)
        {
            cout << "indexing incorrect" << endl;
        }
        
        vector<int> indices;
        for (int j = starting_index; j <= ending_index; ++j)
        {
            indices.push_back(j);
        }
        vector<double> values = rng.vector(num_cols);
        
        mat->insertGlobalValues(i,
                                Teuchos::arrayViewFromVector(indices),
                                Teuchos::arrayViewFromVector(values));
    }
    mat->fillComplete();

    return mat;
}

shared_ptr<Epetra_Vector> get_epetra_vector(int seed,
                                            int size,
                                            shared_ptr<Epetra_Map> map)
{
    Random_Number_Generator<double> rng(-1.,
                                        1.,
                                        seed + 1);
    
    vector<double> data = rng.vector(size);

    shared_ptr<Epetra_Vector> vec
        = make_shared<Epetra_Vector>(*map);
    
    for (int j = 0; j < size; ++j)
    {
        (*vec)[j] = data[j];
    }

    return vec;
}

shared_ptr<TpetraVector> get_tpetra_vector(int seed,
                                           int size,
                                           shared_ptr<TpetraMap> map)
{
    Random_Number_Generator<double> rng(-1.,
                                        1.,
                                        seed + 1);
    
    vector<double> data = rng.vector(size);

    shared_ptr<TpetraVector> vec
        = make_shared<TpetraVector>(Teuchos::rcp(map));
    
    for (int j = 0; j < size; ++j)
    {
        vec->replaceGlobalValue(j, data[j]);
    }
    
    return vec;
}

void test_amesos(int num_matrices,
                 int size,
                 int num_cols)
{
    vector<shared_ptr<Epetra_SerialComm> > comm(num_matrices);
    vector<shared_ptr<Epetra_Map> > map(num_matrices);
    vector<shared_ptr<Epetra_CrsMatrix> > mat(num_matrices);
    vector<shared_ptr<Epetra_Vector> > lhs(num_matrices);
    vector<shared_ptr<Epetra_Vector> > rhs(num_matrices);
    vector<shared_ptr<Epetra_LinearProblem> > problem(num_matrices);
    vector<shared_ptr<Amesos_BaseSolver> > solver(num_matrices);
    
    vector<double> result(num_matrices, 0);
    #pragma omp parallel for
    for (int i = 0; i < num_matrices; ++i)
    {
        // Get comm
        comm[i] = make_shared<Epetra_SerialComm>();

        // Get map
        map[i] = make_shared<Epetra_Map>(size, 0, *comm[i]);
        
        // Get matrix
        mat[i] = get_epetra_matrix(i,
                                   num_cols,
                                   size,
                                   map[i]);

        // Get vectors
        lhs[i] = make_shared<Epetra_Vector>(*map[i]);
        lhs[i]->PutScalar(1.0);
        rhs[i] = get_epetra_vector(i,
                                   size,
                                   map[i]);
        problem[i] = make_shared<Epetra_LinearProblem>(mat[i].get(),
                                                       lhs[i].get(),
                                                       rhs[i].get());
        
        // Get solver
        Amesos factory;
        solver[i] = shared_ptr<Amesos_BaseSolver>(factory.Create("Klu",
                                                                 *problem[i]));
        solver[i]->SymbolicFactorization();
        solver[i]->NumericFactorization();
        
        solver[i]->Solve();

        for (int j = 0; j < size; ++j)
        {
            result[i] += (*rhs[i])[j];
        }
    }

    for (int i = 0; i < num_matrices; ++i)
    {
        cout << i << "\t" << result[i] << endl;
    }
}

void test_aztec_ifpack(int num_matrices,
                       int size,
                       int num_cols)
{
    vector<shared_ptr<Epetra_MpiComm> > comm(num_matrices);
    vector<shared_ptr<Epetra_Map> > map(num_matrices);
    vector<shared_ptr<Epetra_CrsMatrix> > mat(num_matrices);
    vector<shared_ptr<Epetra_Vector> > lhs(num_matrices);
    vector<shared_ptr<Epetra_Vector> > rhs(num_matrices);
    vector<shared_ptr<Epetra_LinearProblem> > problem(num_matrices);
    vector<shared_ptr<Ifpack_Preconditioner> > prec(num_matrices);
    vector<shared_ptr<AztecOO> > solver(num_matrices);
    
    vector<double> result(num_matrices, 0);
    #pragma omp parallel for
    for (int i = 0; i < num_matrices; ++i)
    {
        // Get comm
        comm[i] = make_shared<Epetra_MpiComm>(MPI_COMM_WORLD);

        // Get map
        map[i] = make_shared<Epetra_Map>(size, 0, *comm[i]);
        
        // Get matrix
        mat[i] = get_epetra_matrix(i,
                                   num_cols,
                                   size,
                                   map[i]);

        // Get vectors
        lhs[i] = make_shared<Epetra_Vector>(*map[i]);
        lhs[i]->PutScalar(1.0);
        rhs[i] = get_epetra_vector(i,
                                   size,
                                   map[i]);
        problem[i]
            = make_shared<Epetra_LinearProblem>(mat[i].get(),
                                                lhs[i].get(),
                                                rhs[i].get());

        // Get preconditioner
        Ifpack factory;
        prec[i]
            = shared_ptr<Ifpack_Preconditioner>(factory.Create("ILUT",
                                                               mat[i].get()));
        Teuchos::ParameterList prec_list;
        prec_list.set("fact: drop tolerance", 1e-12);
        prec_list.set("fact: ilut level-of-fill", 1.0);
        prec[i]->SetParameters(prec_list);
        prec[i]->Initialize();
        prec[i]->Compute();

        // Get solver
        solver[i]
            = make_shared<AztecOO>(*problem[i]);
        solver[i]->SetAztecOption(AZ_solver, AZ_gmres);
        solver[i]->SetAztecOption(AZ_kspace, 20);
        solver[i]->SetPrecOperator(prec[i].get());
        solver[i]->SetAztecOption(AZ_output, AZ_warnings);
        
        solver[i]->Iterate(1000,
                           1e-12);
        double const *status = solver[i]->GetAztecStatus();
        switch ((int) status[AZ_why])
        {
        case AZ_normal:
            break;
        case AZ_param:
            cout << "AztecOO: Parameter not available" << endl;
            break;
        case AZ_breakdown:
            cout << "AztecOO: Numerical breakdown" << endl;
            break;
        case AZ_loss:
            cout << "AztecOO: Numerical loss of precision" << endl;
            break;
        case AZ_ill_cond:
            cout << "AztecOO: Ill-conditioned matrix" << endl;
            break;
        case AZ_maxits:
            cout << "AztecOO: Max iterations reached without convergence" << endl;
            break;
        }
        
        for (int j = 0; j < size; ++j)
        {
            result[i] += (*rhs[i])[j];
        }
    }

    for (int i = 0; i < num_matrices; ++i)
    {
        cout << i << "\t" << result[i] << endl;
    }
}

void test_belos_ifpack2(int num_matrices,
                        int size,
                        int num_cols)
{
    vector<shared_ptr<TeuchosComm> > comm(num_matrices);
    vector<shared_ptr<TpetraMap> > map(num_matrices);
    vector<shared_ptr<TpetraCrsMatrix> > mat(num_matrices);
    vector<shared_ptr<TpetraVector> > lhs(num_matrices);
    vector<shared_ptr<TpetraVector> > rhs(num_matrices);
    vector<shared_ptr<BelosLinearProblem> > problem(num_matrices);
    vector<shared_ptr<Ifpack2Preconditioner> > prec(num_matrices);
    vector<shared_ptr<BelosSolverManager> > solver(num_matrices);
    
    vector<double> result(num_matrices, 0);
    #pragma omp parallel for
    for (int i = 0; i < num_matrices; ++i)
    {
        // Get comm
        comm[i] = make_shared<TeuchosSerialComm>();

        // Get map
        map[i] = make_shared<TpetraMap>(size, 0, Teuchos::rcp(comm[i]));
        
        // Get matrix
        mat[i] = get_tpetra_matrix(i,
                                   num_cols,
                                   size,
                                   map[i]);

        // Get vectors
        lhs[i] = make_shared<TpetraVector>(rcp(map[i]));
        lhs[i]->putScalar(1.0);
        rhs[i] = get_tpetra_vector(i,
                                   size,
                                   map[i]);
        // Get preconditioner
        prec[i]
            = make_shared<Ifpack2ILUT>(Teuchos::rcp(mat[i]));
        
        Teuchos::ParameterList ifp_list;
        ifp_list.set("fact: drop tolerance", 1e-12);
        ifp_list.set("fact: ilut level-of-fill", 1.0);
        prec[i]->setParameters(ifp_list);
        prec[i]->initialize();
        prec[i]->compute();

        // Get problem
        problem[i]
            = make_shared<BelosLinearProblem>(Teuchos::rcp(mat[i]),
                                              Teuchos::rcp(lhs[i]),
                                              Teuchos::rcp(rhs[i]));
        
        problem[i]->setLeftPrec(Teuchos::rcp(prec[i]));

        if (!problem[i]->setProblem())
        {
            cout << "Problem set up incorrectly" << endl;
        }

        // Get solver
        shared_ptr<Teuchos::ParameterList> belos_list
            = make_shared<Teuchos::ParameterList>();
        belos_list->set("Maximum Iterations", 400);
        belos_list->set("Convergence Tolerance", 1e-8);
        belos_list->set("Verbosity", Belos::Errors + Belos::Warnings);
        belos_list->set("Num Blocks", 40);
        
        BelosSolverFactory factory;
        solver[i] =
            Teuchos::get_shared_ptr(factory.create("GMRES",
                                                   Teuchos::rcp(belos_list)));
        solver[i]->setProblem(Teuchos::rcp(problem[i]));

        Belos::ReturnType belos_result = solver[i]->solve(); 
        
        for (int j = 0; j < size; ++j)
        {
            result[i] += rhs[i]->getData()[j];
        }
    }

    for (int i = 0; i < num_matrices; ++i)
    {
        cout << i << "\t" << result[i] << endl;
    }
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    
    if (argc != 5)
    {
        cerr << "usage: test [num_procs num_matrices num_rows num_cols_per_row]" << endl;
        return 1;
    }

    int num_procs = atoi(argv[1]);
    int num_matrices = atoi(argv[2]);
    int size = atoi(argv[3]);
    int num_cols = atoi(argv[4]);
    omp_set_num_threads(num_procs);

    // test_amesos(num_matrices,
    //             size,
    //             num_cols);
    test_belos_ifpack2(num_matrices,
                       size,
                       num_cols);
    
    MPI_Finalize();
}

