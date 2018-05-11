#include <iostream>
#include <vector>
using namespace std;

void main( )
{ 
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    try
    {
        cout << v.at(0) << endl;
        cout << v.at(3) << endl;
        cout << v.at(6) << endl; //throw out_of_range ¿¹¿Ü
    }
    catch(out_of_range &e)
    {
        cout << e.what() << endl;
    }
}