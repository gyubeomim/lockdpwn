#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);
    

    if( binary_search(v.begin(), v.end(), 20) )
        cout << "20 원소가 존재합니다." << endl;
    else
        cout << "20 원소가 존재하지 않습니다." << endl;
}