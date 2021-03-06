#include <iostream>
#include <vector>

using namespace std;

class Hello
{
    
public:

    Hello(unsigned &num):
        num_(num)
    {
        hi_.resize(num);

        for (unsigned i = 0; i < num; ++i)
        {
            hi_[i] = i + 1;
        }
    }

    inline double hi(unsigned &i)
    {
        return hi_[i];
    }

    inline unsigned num()
    {
        return num_;
    }
    
private:

    unsigned &num_;
    vector<double> hi_;
    
};

int main()
{
    unsigned num = 10000;
    
    Hello whatup(num);

    // cout << whatup.num() << endl;
    
    // num = 5;

    // cout << whatup.num() << endl;

    double temp = 0;

    for (unsigned t = 0; t < 100000; ++t)
    {
        for (unsigned i = 0; i < num; ++i)
        {
            temp = whatup.hi(i);
        }
    }
}
