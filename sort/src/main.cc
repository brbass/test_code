#include "Points.hh"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "usage: points [num_points dimension bound]" << endl;
        
        return 1;
    }
    
    int num_points = atoi(argv[1]);
    int dimension = atoi(argv[2]);
    double bound = atof(argv[3]);
    
    Points points(num_points,
                  dimension,
                  bound);

    points.find_points(30,
                       10);
}
