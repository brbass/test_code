#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "pugixml.hpp"

using namespace std;

vector<double> getVertexIndices(string const& pointLine)
{
    std::istringstream iss(pointLine);

    return std::vector<double>{std::istream_iterator<double>(iss), std::istream_iterator<double>()};
}


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cerr << "usage: xml_parser [filename]" << endl;
    }

    string filename = argv[1];

    pugi::xml_document doc;

    if (!doc.load_file(filename.c_str())) 
    {
        return -1;
    }
    
    pugi::xml_node regions = doc.child("regions");
    
    for (pugi::xml_node region = regions.child("region"); region; region = region.next_sibling("region"))
    {
        string input = region.child_value("sigma_s");
        vector<double> sigma_t = getVertexIndices(input);
        for (unsigned i=0; i<sigma_t.size(); ++i)
        {
            cout << sigma_t[i] << endl;
        }
        cout << endl;
    }
    
    unsigned number_of_cells = atoi(regions.child("region").child_value("number_of_cells"));
    cout << number_of_cells << endl;

    pugi::xml_node other = doc.child("other");
    
    double hi = atof(other.child_value("hi"));
    cout << hi << endl;
}
