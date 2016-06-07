#ifndef Elephant_hh
#define Elephant_hh

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class Elephant
{
public:

    Elephant();
    
    Elephant(double weight,
             vector<shared_ptr<Elephant> > const &babies = vector<shared_ptr<Elephant> >());

    void initialize(double weight,
                    vector<shared_ptr<Elephant> > const &babies = vector<shared_ptr<Elephant> >());
    
    double weight()
    {
        return weight_;
    }

    shared_ptr<Elephant> baby(int i)
    {
        return babies_[i];
    }
    
// private:
    
    double weight_;
    vector<shared_ptr<Elephant> > babies_;
};

#endif
