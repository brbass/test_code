#include "Identity_Operator.hh"

Identity_Operator::
Identity_Operator(int size):
    size_(size)
{
}

void Identity_Operator::
apply_(vector<double> &x)
{
    for (int i = 0; i < size_; ++i)
    {
        x[i] *= i;
    }
}
