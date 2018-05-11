#include <iostream>
#include <vector>
using namespace std;

void main() 
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    cout<<"v[iterator] : ";
    for(vector<int>::iterator iter= v.begin(); iter != v.end(); ++iter)
        cout << *iter <<" ";
    cout << endl;

    cout<<"v[reverse_iterator] : ";
    for(vector<int>::const_reverse_iterator riter=v.rbegin(); riter != v.rend(); ++riter)
        cout << *riter <<" ";
    cout << endl;
}