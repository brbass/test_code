#include <vector>
#include <iostream>
#include <functional>

using namespace std;

class Cool
{
private:

    unsigned ni = 5;
    unsigned ng = 4;
    
    vector<double> psi_;

public:

    Cool()
    {
        psi_.assign(ni * ng, 0);
    }
    
    inline double &psi(unsigned i, unsigned g)
    {
        return psi_[g + ng * i];
    }
};

int hi()
{
    return 1;
}

int main()
{
    // Cool cool;
    // cout << cool.psi(0, 0) << endl;
    
    // cool.psi(0, 0) = 5;

    // cout << cool.psi(0, 0) << endl;

    function<int()> func;
    func = hi;
    
    cout << func() << endl;
    
}
