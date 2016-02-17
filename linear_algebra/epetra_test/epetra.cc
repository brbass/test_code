#include "Matrix_Solver.hh"

#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <Epetra_SerialDenseMatrix.h>
#include <Epetra_SerialDenseVector.h>
#include <Epetra_SerialDenseSolver.h>

// #include <Epetra_SerialComm.h>
// #include <Epetra_Map.h>
// #include <Epetra_CrsMatrix.h>
// #include <Epetra_MultiVector.h>
// #include <Epetra_LinearProblem.h>
// #include <Amesos.h>

#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "Check.hh"

Matrix_Solver::
Matrix_Solver(unsigned size):
    size_(size)
{
}

void Matrix_Solver::
solve(vector<double> &a_data,
      vector<double> &b_data,
      vector<double> &x_data)
{
    Check(a_data.size() == size()*size(), "A size");
    Check(b_data.size() == size(), "b size");
    Check(x_data.size() == size(), "x size");

    // default solve: gsl > boost
    gsl_solve(a_data,
              b_data,
              x_data);
}

void Matrix_Solver::
gsl_solve(vector<double> &a_data,
          vector<double> &b_data,
          vector<double> &x_data)
{
    Check(a_data.size() == size()*size(), "A size");
    Check(b_data.size() == size(), "b size");
    Check(x_data.size() == size(), "x size");

    // assign data
    gsl_matrix_view a = gsl_matrix_view_array(&a_data[0],
                                              size(),
                                              size());
    gsl_vector_view b = gsl_vector_view_array(&b_data[0],
                                              size());
    gsl_vector_view x = gsl_vector_view_array(&x_data[0],
                                              size());

    // solve
    int s;
    gsl_permutation *p = gsl_permutation_alloc(size());
    gsl_linalg_LU_decomp(&a.matrix, p, &s);
    gsl_linalg_LU_solve(&a.matrix, p, &b.vector, &x.vector);
    gsl_permutation_free(p);
}

void Matrix_Solver::
boost_solve(vector<double> &a_data,
            vector<double> &b_data,
            vector<double> &x_data)
{
    namespace ublas = boost::numeric::ublas;

    Check(a_data.size() == size()*size(), "A size");
    Check(b_data.size() == size(), "b size");
    Check(x_data.size() == size(), "x size");

    // assign data
    ublas::matrix<double> a(size(), size());
    ublas::vector<double> b(size());
    ublas::vector<double> x(size());

    for (unsigned i=0; i<size(); ++i)
    {
        b(i) = b_data[i];

        for (unsigned j=0; j<size(); ++j)
        {
            a(j,i) = a_data[j + size()*i];
        }
    }
    
    ublas::permutation_matrix<double> p(size());
    ublas::lu_factorize(a, p);
    x = b;
    ublas::lu_substitute(a,p,x);
}

void Matrix_Solver::
epetra_solve(vector<double> &a_data,
             vector<double> &b_data,
             vector<double> &x_data)
{
    Check(a_data.size() == size()*size(), "A size");
    Check(b_data.size() == size(), "b size");
    Check(x_data.size() == size(), "x size");

    Epetra_SerialDenseMatrix a(View, &a_data[0], size(), size(), size());
    Epetra_SerialDenseVector x(size());
    Epetra_SerialDenseVector b(View, &b_data[0], size());

    Epetra_SerialDenseSolver solver;

    solver.FactorWithEquilibration(true);
    solver.SetMatrix(a);
    solver.SetVectors(x, b);
    solver.Solve();

    x_data.assign(solver.X(), solver.X() + size());
}

// void Matrix_Solver::
// amesos_solve(vector<double> &a_data,
//              vector<double> &b_data,
//              vector<double> &x_data,
//              vector<unsigned> &num_entries_per_row)
// {
//     Check(num_entries_per_row.size() == size(), "num_entries_per_row size");
//     {
//         unsigned sum = 0;
//         for (unsigned i=0; i<size(); ++i)
//         {
//             sum += num_entries_per_row[i];
//         }
//         Check(a_data.size() == sum, "A size");
//     }
//     Check(b_data.size() == size(), "b size");
//     Check(x_data.size() == size(), "x size");

//     const int index_base_ = 0;
//     int num_global_elements_ = 0; // number of global rows      
//     int num_matrices_ = 0;
//     int num_my_elements_ = 0; // number of local rows                    
//     const int num_vectors_ = 1; // number of solution/source vectors     

//     vector<int> num_entries_per_row_;
//     vector<int> my_global_elements_;

//     Epetra_Map *map_ = 0;
//     Epetra_SerialComm *comm_ = 0;
//     vector<Epetra_CrsMatrix> matrix_;
//     vector<Epetra_MultiVector> lhs_;
//     vector<Epetra_MultiVector> rhs_;
//     vector<Epetra_LinearProblem> problem_;

//     default_random_engine generator_;
//     uniform_real_distribution<double> distribution_;

//     string solver_type_ = "Klu";

//     vector<Amesos_BaseSolver*> solver_;
//     Amesos factory_;
//     Teuchos::ParameterList list_;

// }
