#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    int a=10, b=20;

    vector<int> v;
    v.push_back(10);
    v.push_back(20);

    cout << "a= "<< a <<", " <<"b= "<< b << endl;
    swap(a, b);
    cout << "a= "<< a <<", " <<"b= "<< b << endl;

    vector<int>::iterator p = v.begin();
    vector<int>::iterator q = v.begin()+1;

    cout << "v[0]= "<< v[0] <<", " <<"v[1]= "<< v[1] << endl;
    iter_swap(p, q);
    cout << "v[0]= "<< v[0] <<", " <<"v[1]= "<< v[1] << endl;
}