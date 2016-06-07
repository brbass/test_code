#include "Elephant.hh"

#include <iostream>

using namespace std;

int main()
{
    vector<shared_ptr<Elephant> > children(2);
    children[0] = make_shared<Elephant>();
    children[1] = make_shared<Elephant>();
    
    shared_ptr<Elephant> mom = make_shared<Elephant>(50,
                                                     children);
    
    children[0]->initialize(10);
    children[1]->initialize(20);

    shared_ptr<Elephant> baby;
    
    cout << children[0] << endl;
    cout << mom->baby(0) << endl;
    
    cout << mom->baby(0)->weight() << endl;
    cout << mom->baby(1)->weight() << endl;
    
    cout << mom->weight() << endl;
}
