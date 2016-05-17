#include <iostream>
#include <string>

#include <AztecOO.h>
#include <mpi.h>
#include <Epetra_CrsMatrix.h>
#include <Epetra_MpiComm.h>
#include <Epetra_Map.h>
#include <Epetra_Operator.h>
#include <Epetra_Vector.h>
#include <Epetra_LinearProblem.h>

#include "Epetra_Operator_Interface.hh"
#include "Identity_Operator.hh"

using namespace std;

class Epetra_Test : public Epetra_Operator
{
public:
    
    Epetra_Test(shared_ptr<Epetra_Comm> const &comm,
                shared_ptr<Epetra_Map> const &map):
        comm_(comm),
        map_(map)
    {
    }

    ~Epetra_Test()
    {
    }
    
    virtual int SetUseTranspose(bool UseTranspose)
    {
        return -1;
    }

    virtual int Apply(Epetra_MultiVector const &X,
                      Epetra_MultiVector &Y) const
    {
        return 0;
    }

    virtual int ApplyInverse(Epetra_MultiVector const &X,
                             Epetra_MultiVector &Y) const
    {
        return 1;
    }

    virtual double NormInf() const
    {
        return 0.;
    }

    virtual const char *Label() const
    {
        return "Epetra_Interface";
    }

    virtual bool UseTranspose() const
    {
        return false;
    }

    virtual bool HasNormInf() const
    {
        return false;
    }

    virtual const Epetra_Comm &Comm() const
    {
        return *comm_;
    }
    
    virtual const Epetra_Map &OperatorDomainMap() const
    {
        return *map_;
    }

    virtual const Epetra_Map &OperatorRangeMap() const
    {
        return *map_;
    }

private:

    shared_ptr<Epetra_Comm> comm_;
    shared_ptr<Epetra_Map> map_;

};

void test_minimal()
{
    int size = 10;
    int kspace = 100;
    int max_iterations = 5000;
    double tolerance = 1e-6;
    int solver_print = 1;

    vector<double> x(size, 1);

    shared_ptr<Epetra_Comm> comm = make_shared<Epetra_MpiComm>(MPI_COMM_WORLD);
    shared_ptr<Epetra_Map> map = make_shared<Epetra_Map>(size, 0, *comm);
    shared_ptr<Epetra_Vector> lhs = make_shared<Epetra_Vector>(*map);
    shared_ptr<Epetra_Vector> rhs = make_shared<Epetra_Vector>(*map);
    shared_ptr<Epetra_Operator> oper = make_shared<Epetra_Test>(comm,
                                                                map);
    
    shared_ptr<Epetra_LinearProblem> problem = make_shared<Epetra_LinearProblem>(oper.get(),
                                                                                 lhs.get(),
                                                                                 rhs.get());
    
    cout << problem->CheckInput() << endl;
    shared_ptr<AztecOO> solver = make_shared<AztecOO>(*problem);
    
    solver->SetAztecOption(AZ_solver, AZ_gmres);
    solver->SetAztecOption(AZ_kspace, kspace);
    solver->SetAztecOption(AZ_precond, AZ_none);
    if (solver_print)
    {
        solver->SetAztecOption(AZ_output, AZ_all);
    }
    else
    {
        solver->SetAztecOption(AZ_output, AZ_none);
    }
    
    lhs->PutScalar(2.0);
    rhs->PutScalar(1.0);
    
    solver->Iterate(max_iterations, tolerance);
    
    lhs->ExtractCopy(&x[0]);
    
    for (int i = 0; i < size; ++i)
    {
        cout << x[i] << endl;
    }
}

void solve_problem()
{
    int size = 10;
    
    int poly_ord = 3;
    int kspace = 100;
    int max_iterations = 5000;
    double tolerance = 1e-6;
    int solver_print = 1;

    vector<double> x(size, 0);

    shared_ptr<Vector_Operator> VO = make_shared<Identity_Operator>(size);
    shared_ptr<Epetra_Comm> comm = make_shared<Epetra_MpiComm>(MPI_COMM_WORLD);
    shared_ptr<Epetra_Map> map = make_shared<Epetra_Map>(size, 0, *comm);
    shared_ptr<Epetra_Vector> lhs = make_shared<Epetra_Vector>(*map);
    shared_ptr<Epetra_Vector> rhs = make_shared<Epetra_Vector>(*map);
    shared_ptr<Epetra_Operator> oper = make_shared<Epetra_Operator_Interface>(comm,
                                                                              map,
                                                                              VO);
    shared_ptr<Epetra_CrsMatrix> mat = make_shared<Epetra_CrsMatrix>(Copy, *map, 1, true);
    for (int i = 0; i < size; ++i)
    {
        double val = i + 1;
        mat->InsertGlobalValues(i, 1, &val, &i);
    }
    mat->FillComplete();
    shared_ptr<Epetra_Operator> mat1 = dynamic_pointer_cast<Epetra_Operator>(mat);
    shared_ptr<Epetra_LinearProblem> problem = make_shared<Epetra_LinearProblem>(oper.get(),
                                                                                 lhs.get(),
                                                                                 rhs.get());
    
    cout << problem->CheckInput() << endl;
    shared_ptr<AztecOO> solver = make_shared<AztecOO>(*problem);
    
    solver->SetAztecOption(AZ_solver, AZ_gmres);
    solver->SetAztecOption(AZ_kspace, kspace);
    solver->SetAztecOption(AZ_precond, AZ_none);
    if (solver_print)
    {
        solver->SetAztecOption(AZ_output, AZ_all);
    }
    else
    {
        solver->SetAztecOption(AZ_output, AZ_none);
    }
    
    lhs->PutScalar(0.0);
    rhs->PutScalar(1.0);
    
    solver->Iterate(max_iterations, tolerance);
    
    lhs->ExtractCopy(&x[0]);
    
    for (int i = 0; i < size; ++i)
    {
        cout << x[i] << endl;
    }
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    // test_minimal();
    solve_problem();

    MPI_Finalize();
}
