#include <iostream>
#include <vector>

using namespace std;

template<class T>
int num(vector<T> &vec)
{
    return vec.size();
}

template<class T>
int num2(T &ans)
{
    return 1;
}

int main()
{
    vector<double> test1(5, 1);
    vector<unsigned> test2(4, 2);

    cout << num(test1) << endl;
    cout << num(test2) << endl;

    double test3 = 3;
    unsigned test4 = 5;

    cout << num2(test3) << endl;
    cout << num2(test4) << endl;
}
