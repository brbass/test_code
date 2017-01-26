#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int length1 = 4;
    int length2 = 2;
    vector<vector<double> > vec(length1, vector<double>(length2, 0));

    for (int i = 0; i < length1; ++i)
    {
        for (int j = 0; j < length2; ++j)
        {
            cout << vec[i][j] << endl;
        }
    }
}
