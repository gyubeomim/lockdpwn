#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2;
    v2.push_back(10);
    v2.push_back(20);
    v2.push_back(30);
    v2.push_back(80);
    v2.push_back(90);

    pair<vector<int>::iterator, vector<int>::iterator> iter_pair;
    iter_pair = mismatch(v1.begin(),v1.end(),v2.begin());

    cout <<"v1: "<< *iter_pair.first <<", " <<"v2: "<<*iter_pair.second << endl;
}