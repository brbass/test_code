#ifndef Points_hh
#define Points_hh

#include <memory>
#include <vector>

#include "nanoflann.hpp"

using std::shared_ptr;
using std::vector;

class Points
{
private: class KD_Adaptor;
    
public:

    
    typedef nanoflann::L2_Adaptor<double,
                                  KD_Adaptor> L2A;
    typedef nanoflann::KDTreeSingleIndexAdaptor<L2A,
                                                KD_Adaptor> KDT;
    
    Points(int num_points,
           int dimension);
    
private:
    
    int num_points_;
    int dimension_;

    vector<double> data_;

    void find_points(int num,
                     int index);

    shared_ptr<KD_Adaptor> adaptor_;
    shared_ptr<KDT> kd_tree_;
    
    class KD_Adaptor
    {
    public:
        
        KD_Adaptor(Points const &points);
        
        inline int kdtree_get_point_count() const
        {
            return points_.num_points_;
        }

        inline double kdtree_get_pt(const int idx, int dim) const
        {
            return points_.data_[dim + points_.dimension_ * idx];
        }

        inline double kdtree_distance(const double *p1, const int idx_p2, int /*size*/)
        {
            double sum = 0;

            for (int i = 0; i < points_.dimension_; ++i)
            {
                double dist = (p1[i] - points_.data_[i + points_.dimension_ * idx_p2]);
                
                sum += dist * dist;
            }
            
            return sum;
        }
        
        template <class BBOX>
        bool kdtree_get_bbox(BBOX &/*bb*/) const
        {
            return false;
        }
        
    private:
        
        Points const &points_;
    };

};

#endif
