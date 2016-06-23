#ifndef Test_Tpetra_hh
#define Test_Tpetra_hh

class Test_Tpetra
{
public:

    Test_Tpetra(int size);

    void test1();

private:

    int index_base_ = 0;
    int size_;
};

#endif
