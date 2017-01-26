#include <iostream>
#include <random>

namespace
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0, 1);
    
    double random_real()
    {
        return distribution(generator);
    }
}

class Point
{
public:
    double x;
    double y;
};

Point rejection1()
{
    Point p;
    
    double z = 1.0;
    double f = 0;
    while(z > f)
    {
        p.x = random_real();
        p.y = random_real();
        z = 3.0 * random_real();
        f = 3.0 * p.x * (1. - p.x * p.y);
    }
    return p;
}

Point rejection2()
{
    Point p;
    p.x = random_real();
    p.y = random_real();

    double z = 3.0 * random_real();
    double f = 3.0 * p.x * (1. - p.x * p.y);

    if (z < f)
    {
        return p;
    }
    else
    {
        return rejection2();
    }
    
}


int main()
{
    int num_samples = 1e6;

    double Ex = 0.0;
    double Ey = 0.0;
    double Exy = 0.0;

    for (int i = 0; i < num_samples; ++i)
    {
        Point p = rejection1();
        Ex += p.x;
        Ey += p.y;
        Exy += p.x * p.y;
    }
}
