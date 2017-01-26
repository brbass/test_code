#include <iostream>
#include <vector>

#include "Random_Number_Generator.hh"
#include "Timer.hh"
#include "Vector_3D.hh"
#include "Vector_Constructor.hh"

using namespace std;

Random_Number_Generator<double> rng(0.0, 1.0);
Timer timer;

void vector_access()
{
    cout << "VECTOR ACCESS" << endl;
    int iter = 100000;
    int num1 = 1000;
    int num2 = 100;
    int num3 = 100;
    int numt = num1 * num2 * num3;
    vector<double> data = rng.vector(num1 * num2 * num3);
    Vector_3D<double> data3d(num1,
                             num2,
                             num3,
                             data);
    
    timer.start();
    for (int a = 0; a < iter; ++a)
    {
        double sum = 0;
        for (int i = 0; i < numt; ++i)
        {
            sum += data[i];
        }
    }
    timer.stop();
    cout << "normal access:\t" << timer.time() << endl;

    timer.start();
    for (int a = 0; a < iter; ++a)
    {
        double sum = 0;
        for (int i = 0; i < num1; ++i)
        {
            for (int j = 0; j < num2; ++j)
            {
                for (int k = 0; k < num3; ++k)
                {
                    int l = k + num3 * (j + num2 * i);
                    sum += data[k];
                }
            }
        }
    }
    timer.stop();
    cout << "index access w/ int:\t" << timer.time() << endl;

    timer.start();
    for (int a = 0; a < iter; ++a)
    {
        double sum = 0;
        for (int i = 0; i < num1; ++i)
        {
            for (int j = 0; j < num2; ++j)
            {
                for (int k = 0; k < num3; ++k)
                {
                    sum += data[k + num3 * (j + num2 * i)];
                }
            }
        }
    }
    timer.stop();
    cout << "index access w/o int:\t" << timer.time() << endl;
    
    timer.start();
    for (int a = 0; a < iter; ++a)
    {
        double sum = 0;
        for (int i = 0; i < num1; ++i)
        {
            for (int j = 0; j < num2; ++j)
            {
                for (int k = 0; k < num3; ++k)
                {
                    sum += data3d(i, j, k);
                }
            }
        }
    }
    timer.stop();
    cout << "class access :\t" << timer.time() << endl;

    cout << endl;
}

void vector_creation()
{
    cout << "VECTOR CREATION" << endl;
    int iter = 1000000;
    int num = 1000;
    vector<double> data = rng.vector(num);
    
    timer.start();
    for (int a = 0; a < iter; ++a)
    {
        Vector_Constructor_1 vc1(data);
    }
    timer.stop();
    cout << "const ref, copy :\t" << timer.time() << endl;

    timer.start();
    for (int a = 0; a < iter; ++a)
    {
        Vector_Constructor_2 vc2(data);
    }
    timer.stop();
    cout << "copy, copy :\t" << timer.time() << endl;
    
    timer.start();
    for (int a = 0; a < iter; ++a)
    {
        Vector_Constructor_3 vc3(data);
    }
    timer.stop();
    cout << "ref, ref :\t" << timer.time() << endl;

    cout << endl;
}

int main()
{
    vector_access();
    vector_creation();
    return 0;
}
