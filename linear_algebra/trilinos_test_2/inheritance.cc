#include <iostream>
#include <vector>

using namespace std;

class Neutronics
{
private:

    vector<double> sigma_t_;

public:

    Neutronics(unsigned length,
               double val):
        sigma_t_(length, val)
    {
    }

    virtual void solve()
    {
        cerr << "no transport model defined" << endl;
    }
    
    inline double &sigma_t(unsigned i)
    {
        return sigma_t_[i];
    }
};

class Monte_Carlo: public Neutronics
{
private:

    double num_particles_;
    
public:

    Monte_Carlo(unsigned length,
                double val,
                unsigned num_particles):
        Neutronics(length,
                   val),
        num_particles_(num_particles)
    {
    }

    void print(unsigned i)
    {
        cout << sigma_t(i) << endl;
    }

    virtual void solve()
    {
        cout << "monte carlo transport used" << endl;
    }
    
    inline double num_particles()
    {
        return num_particles_;
    }
};

int main()
{
    unsigned length = 5;
    double val = 10.0;
    unsigned num_particles = 5;
    
    Monte_Carlo monte_carlo(length,
                            val,
                            num_particles);

    monte_carlo.solve();

    Neutronics neutronics(length,
                          val);

    neutronics.solve();

    Neutronics *neutronics2;

    neutronics2 = new Monte_Carlo(length,
                                 val,
                                 num_particles);

    neutronics2->solve();
    
    for (unsigned i = 0; i < length; ++i)
    {
        cout << monte_carlo.sigma_t(i) << endl;
        monte_carlo.print(i);
    }
    
}

    
