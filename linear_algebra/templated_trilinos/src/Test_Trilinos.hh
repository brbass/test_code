#ifndef Test_Trilinos_hh
#define Test_Trilinos_hh

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class Test_Trilinos
{
public:

    Test_Trilinos(int size,
                  double dx,
                  double sigma_a,
                  double q,
                  bool print = true);

    void test1();
    void test2();
    
private:

    int index_base_ = 0;
    size_t size_;
    double dx_;
    double sigma_a_;
    double q_;
    bool print_;
    
    vector<size_t> num_entries_per_row_;
};

#endif
