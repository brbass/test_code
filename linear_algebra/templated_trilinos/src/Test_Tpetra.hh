#ifndef Test_Tpetra_hh
#define Test_Tpetra_hh

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class Test_Tpetra
{
public:

    Test_Tpetra(int size);

    void test1();

private:

    int index_base_ = 0;
    int size_;

    shared_ptr<vector<int> > num_entries_per_row_;
};

#endif
