#include <iostream>
#include <algorithm>
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
    v.push_back(40);
    v.push_back(50);

    cout <<"v : ";
    copy(v.begin(), v.end(), ostream_iterator<int>(cout) );
    cout <<endl;

    cout <<"v : ";
    copy(v.begin(), v.end(), ostream_iterator<int>(cout,", ") );
    cout <<endl;

    list<int> lt;
    lt.push_back(100);
    lt.push_back(200);
    lt.push_back(300);

    cout <<"lt+v : ";
    transform(lt.begin(), lt.end(), v.begin(), ostream_iterator<int>(cout,"  "), plus<int>() );
    cout <<endl;
}