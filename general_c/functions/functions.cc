#include <iostream>
#include <functional>
#include <vector>

using namespace std;

class Dog
{
public:
    Dog()
    {
    }

    void bark(function<double(int,
                              int,
                              vector<double> const &)> func
              = [](int g,
                   int m,
                   vector<double> const &position){return 1.;})
    {
        vector<double> position = {2., 5.};
        cout << func(0,
                     0,
                     position);
        cout << endl;
    }
};

int main()
{
    function<double(int,
                    int,
                    vector<double> &)> func
        = [](int g,
             int m,
             vector<double> const &position)
        {
            cout << g << endl;
            cout << m << endl;
            cout << position[0] << endl;
            return g * m * position[0];
        };
    
    vector<double> position = {4., 2.};
    func(1, 3, position);
    
    Dog dog;
    
    dog.bark();
}
