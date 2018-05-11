#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool Pred(int left, int right)
{
    return abs(right-left) <= 5; 
}
void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2;
    v2.push_back(11);
    v2.push_back(25);
    v2.push_back(33);
    v2.push_back(46);
    v2.push_back(50);

    pair<vector<int>::iterator, vector<int>::iterator> iter_pair;
    iter_pair = mismatch(v1.begin(),v1.end(),v2.begin(), Pred);

    cout <<"v1: "<< *iter_pair.first <<", " <<"v2: "<<*iter_pair.second << endl;
}