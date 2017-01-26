#ifndef Vector_3D_hh
#define Vector_3D_hh

#include <iostream>
#include <vector>

template<class Scalar>
class Vector_3D
{
public:
    
    Vector_3D(int num1,
              int num2,
              int num3,
              std::vector<Scalar> data):
        num1_(num1),
        num2_(num2),
        num3_(num3),
        data_(data)
    {
    }
    
    Scalar &operator()(int i,
                       int j,
                       int k)
    {
        // int l = k + num3_ * (j + num2_ * i);
        int l = sub2ind(i,
                        j,
                        k);
        return data_[l];
    }
    
    int sub2ind(int i,
                int j,
                int k)
    {
        return k + num3_ * (j + num2_ * i);
    }
    
private:

    int num1_;
    int num2_;
    int num3_;

    std::vector<Scalar> data_;
};

#endif
