#include <boost/numeric/ublas/banded.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
//#include "umfpack.h"

namespace ublas = boost::numeric::ublas;

class boost_test
{
private:
    ublas::banded_matrix<double> A_;
    ublas::vector<double> B_;
    ublas::vector<double> x_;
    
    unsigned n_;
public:
    boost_test(unsigned n)
    {
        n_ = n;
        A_.resize(n, n, 0, 0);
        B_.resize(n);           
        
        for (unsigned i = 0; i < n; ++i)
        {
            A_(i, i) = n - i;
            B_(i) = 0.1 * i;
        }
    }
    void solve_system()
    {
        ublas::permutation_matrix<double> P_(n_);
        ublas::lu_factorize(A_, P_);
        x_ = B_;
        ublas::lu_substitute(A_,P_,x_);
    }
    void print_result()
    {
        std::cout << A_ << std::endl;
        std::cout << B_ << std::endl;
        std::cout << x_ << std::endl;
    }
};

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "./test [n]" << std::endl;
        return 1;
    }

    unsigned n = std::atoi(argv[1]);
    
    boost_test problem(n);
    problem.solve_system();
}

