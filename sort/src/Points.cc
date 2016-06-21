#include "Points.hh"

#include "Random_Number_Generator.hh"

using namespace std;

Points::
Points(int num_points,
       int dimension):
    num_points_(num_points),
    dimension_(dimension)
{
    Random_Number_Generator rng(-1, 1);
    
    data_ = rng.random_double_vector(num_points * dimension);
}

void Points::
find_points(int num,
            int index)
{
    adaptor_ = make_shared<KD_Adaptor>(*this);
    kd_tree_ = make_shared<KDT>(dimension_,
                                *adaptor_);

    kd_tree_->buildIndex();
                                     
}

Points::KD_Adaptor::
KD_Adaptor(Points const &points):
    points_(points)
{
    
}
