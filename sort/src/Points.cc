#include "Points.hh"

#include <iomanip>
#include <iostream>

#include "Random_Number_Generator.hh"

using namespace std;

Points::
Points(int num_points,
       int dimension,
       double bound):
    num_points_(num_points),
    dimension_(dimension)
{
    Random_Number_Generator rng(-bound, bound);
    
    data_ = rng.random_double_vector(num_points * dimension);
    
    data_.resize(num_points);
    
    // double dx = bound / num_points;
    
    // for (int i = 0; i < num_points; ++i)
    // {
    //     for (int d = 0; d < dimension; ++d)
    //     {
    //         data_[d + dimension * i] = dx * i;
    //     }
    // }
}

void Points::
find_points(int num,
            int index)
{
    if (!adaptor_)
    {
        adaptor_ = make_shared<KD_Adaptor>(*this);
    }
    if (!kd_tree_)
    {
        kd_tree_ = make_shared<KDT>(dimension_,
                                    *adaptor_);
        kd_tree_->buildIndex();
    }
    
    vector<double> point(dimension_);
    vector<int> indices(num, 0);
    vector<double> distances(num, 0);

    cout << setw(16) << index;
    cout << setw(16) << 0;
    
    for (int i = 0; i < dimension_; ++i)
    {
        point[i] = data_[i + dimension_ * index];

        cout << setw(16) << point[i];
    }
    cout << endl;
    
    kd_tree_->knnSearch(&point[0],
                        num,
                        &indices[0],
                        &distances[0]);
    
    for (int i = 0; i < num; ++i)
    {
        cout << setw(16) << indices[i];
        cout << setw(16) << distances[i];

        for (int d = 0; d < dimension_; ++d)
        {
            cout << setw(16) << data_[d + dimension_ * indices[i]];
        }
        cout << endl;
    }
}

Points::KD_Adaptor::
KD_Adaptor(Points const &points):
    points_(points)
{
    
}
