#include <iostream>
#include <memory>
#include <vector>

#include <mpi.h>

#include "Epetra_Operator_Interface.hh"
#include "Identity_Operator.hh"
#include "Vector_Operator.hh"

#include <Epetra_MpiComm.h>
#include <Epetra_Map.h>
#include <Epetra_Vector.h>

using namespace std;

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int number_of_elements = 10;

    shared_ptr<Epetra_Comm> comm = make_shared<Epetra_MpiComm>(MPI_COMM_WORLD);
    shared_ptr<Epetra_Map> map = make_shared<Epetra_Map>(number_of_elements, 0, *comm);
    shared_ptr<Epetra_Vector> X = make_shared<Epetra_Vector>(*map);
    // shared_ptr<Epetra_Vector> Y = make_shared<Epetra_Vector>(*map);
    
    X->PutScalar(1.0);
    
    shared_ptr<Vector_Operator> oper = make_shared<Identity_Operator>(number_of_elements);
    
    Epetra_Operator_Interface interface(comm,
                                        map,
                                        oper);
    
    interface.Apply(*X, *X);
    
    cout << (*X) << endl;

    MPI_Finalize();
}
