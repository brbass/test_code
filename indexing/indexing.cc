#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int subscript_to_index(int dimension,
                       vector<int> const &size,
                       vector<int> const &subscript)
{
    int index = subscript[0];
    
    for (int d = 1; d < dimension; ++d)
    {
        index = subscript[d] + size[d] * index;
    }

    return index;
}

vector<int> index_to_subscript(int dimension,
                               int index,
                               vector<int> const &size)
{
    vector<int> subscript(dimension);
    
    int product = 1;
    for (int i = 1; i < dimension; ++i)
    {
        product *= size[i];
    };
    
    int sum = index;
    for (int i = 0; i < dimension - 1; ++i)
    {
        subscript[i] = floor(static_cast<double>(sum) / product);
        
        sum -= product * subscript[i];
        product /= size[i + 1];
    }
    
    subscript[dimension - 1] = sum;
    
    return subscript;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cout << "indexing [dimension max_subscript num_attempts conversions_per_attempt]" << endl;
        return 1;
    }
    int dimension = atoi(argv[1]);
    int max_subscript = atoi(argv[2]);
    int num_attempts = atoi(argv[3]);
    int conversions_per_attempt = atoi(argv[4]);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> local_distribution(0, max_subscript);
    
    int total_size = 1;
    vector<int> size(dimension);
    for (int d = 0; d < dimension; ++d)
    {
        int local_size = local_distribution(generator);
        
        size[d] = local_size;
        total_size *= local_size;
    }

    std::uniform_int_distribution<int> distribution(0, total_size);

    for (int i = 0; i < num_attempts; ++i)
    {
        int index = distribution(generator);

        cout << index << "\t";

        for (int j = 0; j < conversions_per_attempt; ++j)
        {
            vector<int> subscript = index_to_subscript(dimension,
                                                       index,
                                                       size);
            index = subscript_to_index(dimension,
                                       size,
                                       subscript);

            cout << index << "\t";
        }
        
        cout << endl;
    }
}

