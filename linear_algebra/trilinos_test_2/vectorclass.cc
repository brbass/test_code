#include <vector>

using namespace std;

class One;

class Two
{
public:
    Two(One &one):
        one_(one)
    {
    }
private:

    One &one_;
};

class One
{
public:

    One()
    {
        Two two(*this);
        twos_.push_back(two);
    }

private:

    vector<Two> twos_;
};


int main()
{
    One one;
}
