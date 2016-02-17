#include <random>
#include <vector>

#include "trilinos_test.hh"

int main()
{
    int size = 10;
    vector<double> matrix(size*size, 0);
    vector<double> lhs(size, 0);
    vector<double> rhs(size, 0);
    
    for (unsigned i=0; i<size; ++i)
    {
        for (unsigned j=0; j<size; ++j)
        {
            matrix[j + i*size] = 2.*i + 3.*j;
        }
        
        rhs[i] = i + 1;
    }

    epetra_solve(matrix, lhs, rhs, size);
}
