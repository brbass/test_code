#include "Elephant.hh"

Elephant::
Elephant()
{
}

Elephant::
Elephant(double weight,
         vector<shared_ptr<Elephant> > const &babies):
    weight_(weight),
    babies_(babies)
{
}

void Elephant::
initialize(double weight,
           vector<shared_ptr<Elephant> > const &babies)
{
    weight_ = weight;
    babies_ = babies;
}
