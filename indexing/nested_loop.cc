#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void nested_loop(int dimension,
                 vector<int> starting_subscript,
                 vector<int> ending_subscript)
{
    vector<int> current_subscript(starting_subscript);

    bool completed = false;

    for (int d = 0; d < dimension; ++d)
    {
        cout << starting_subscript[d] << "\t" << ending_subscript[d] << endl;
    }
    cout << endl;
    
    while (!completed)
    {
        // Print current value
        for (int d = 0; d < dimension; ++d)
        {
            cout << current_subscript[d] << "\t";
        }
        cout << endl;

        for (int d = 0; d < dimension; ++d)
        {
            current_subscript[d] += 1;
            if (current_subscript[d] <= ending_subscript[d])
            {
                break;
            }
            else
            {
                if (d == dimension - 1)
                {
                    completed = true;
                    break;
                }
                else
                {
                    current_subscript[d] = starting_subscript[d];
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "nested_loop [dimension max_number]" << endl;
        return 1;
    }
    int dimension = atoi(argv[1]);
    int max_number = atoi(argv[2]);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, max_number);

    vector<int> starting_subscript(dimension);
    vector<int> ending_subscript(dimension);

    for (int d = 0; d < dimension; ++d)
    {
        starting_subscript[d] = distribution(generator);
        ending_subscript[d] = starting_subscript[d] + distribution(generator);
    }
    
    nested_loop(dimension,
                starting_subscript,
                ending_subscript);
}
