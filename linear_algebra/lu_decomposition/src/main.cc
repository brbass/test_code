#include <cmath>
#include <iostream>
#include <vector>

#include <Epetra_SerialDenseMatrix.h>
#include <Epetra_SerialDenseVector.h>
#include <Epetra_SerialDenseSolver.h>

#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "Timer.hh"

using namespace std;

int num_points = 50;
double length = 1.;
double dx = length / num_points;
double c = 0.5 / dx;

double basis(int i, int j)
{
    double dist = dx * (j - i);
    
    return exp(-c*c*dist*dist);
}

vector<double> get_a_data()
{
    vector<double> a_data(num_points * num_points);
    
    for (int i = 0; i < num_points; ++i)
    {
        for (int j = 0; j < num_points; ++j)
        {
            a_data[j + num_points * i] = basis(i, j);
        }
    }

    return a_data;
}

vector<double> get_b_data()
{
    vector<double> b_data(num_points);
    
    for (int i = 0; i < num_points; ++i)
    {
        b_data[i] = i;
    }

    return b_data;
}

int main()
{
    bool print = false;
    int num_solves = 10000;

    Timer timer;

    vector<double> a_data(get_a_data());
    vector<double> b_data(get_b_data());
    
    {
        timer.start();
        
        gsl_matrix *a = gsl_matrix_alloc(num_points, num_points);
        gsl_permutation *p = gsl_permutation_alloc(num_points);
        
        for (int i = 0; i < num_points; ++i)
        {
            for (int j = 0; j < num_points; ++j)
            {
                gsl_matrix_set(a, i, j, a_data[j + num_points * i]);
            }
        }

        int s;
        gsl_linalg_LU_decomp(a, p, &s);

        timer.stop();

        cout << setw(16) << "GSL init" << setw(16) << timer.time() << endl;
        
        timer.start();
        
        for (int t = 0; t < num_solves; ++t)
        {
            vector<double> b_temp(b_data);
            vector<double> x_temp(num_points);
            
            gsl_vector_view x = gsl_vector_view_array(&x_temp[0],
                                                      num_points);
            gsl_vector_view b = gsl_vector_view_array(&b_temp[0],
                                                      num_points);
            
            gsl_linalg_LU_solve(a, p, &b.vector, &x.vector);

            if (print)
            {
                for (int i = 0; i < num_points; ++i)
                {
                    cout << x_temp[i] << "\t";
                }
                cout << endl;
            }
        }
        
        timer.stop();
        
        cout << setw(16) << "GSL solve" << setw(16) << timer.time() << endl;

        gsl_matrix_free(a);
        gsl_permutation_free(p);
    }

    {
        timer.start();
        
        Epetra_SerialDenseMatrix a(Copy, &a_data[0], num_points, num_points, num_points);

        Epetra_SerialDenseSolver solver;

        solver.SetMatrix(a);
        solver.SolveWithTranspose(true);
        solver.Factor();

        timer.stop();
        
        cout << setw(16) << "Epetra init" << setw(16) << timer.time() << endl;

        timer.start();

        for (int t = 0; t < num_solves; ++t)
        {
            vector<double> b_temp(b_data);
            vector<double> x_temp(num_points);

            Epetra_SerialDenseVector x(View, &x_temp[0], num_points);
            Epetra_SerialDenseVector b(View, &b_temp[0], num_points);

            solver.SetVectors(x, b);

            solver.Solve();

            x_temp.assign(solver.X(), solver.X() + num_points);
            
            if (print)
            {
                cout << x << endl;

                for (int i = 0; i < num_points; ++i)
                {
                    cout << x_temp[i] << "\t";
                }
                cout << endl;
            }
        }

        timer.stop();

        cout << setw(16) << "Epetra solve" << setw(16) << timer.time() << endl;
    }
    
}
