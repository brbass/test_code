#include <iostream>
#include <memory>

using namespace std;

class Hi
{
public:
    Hi()
    {
    }
    
    void speak()
    {
        cout << "hi" << endl;
    }
    
};

shared_ptr<Hi> create_hi()
{
    Hi hello;
    
    // return make_shared<Hi>(hello);
    return shared_ptr<Hi>(hello);
}

int main()
{
    shared_ptr<Hi> hi = create_hi();
    hi->speak();
}
