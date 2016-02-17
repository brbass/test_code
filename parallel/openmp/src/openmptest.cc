#include "omp.h"

int main()
{
    vector<double> hi = {10, 20, 30, 40};
    
    #pragma omp parallel
    {
        int ID = 0;
        
        printf("hello(%d)", ID);
    }
}
