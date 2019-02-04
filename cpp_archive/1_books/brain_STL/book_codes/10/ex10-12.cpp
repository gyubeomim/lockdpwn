#include <iostream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

void main() 
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    list<int> lt;
    lt.push_back(10);
    lt.push_back(20);
    lt.push_back(30);

    cout <<"[v.begin(), v.end())의 원소 개수: " << 
        distance(v.begin(), v.end()) << endl; //v.end()-v.begin()
    cout <<"[lt.begin(), lt.end())의 원소 개수: " << 
        distance(lt.begin(), lt.end()) << endl; 
 }