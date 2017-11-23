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

    list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);
    lt1.push_back(3);

    list<int> lt2;
    lt2.push_back(1);
    lt2.push_back(2);
    lt2.push_back(3);

    copy(v.begin(), v.end(), back_inserter<list<int> >(lt1) );
    copy(v.begin(), v.end(), front_inserter<list<int> >(lt2) );

    cout<<"v : ";
    for(vector<int>::iterator iter=v.begin(); iter != v.end(); ++iter)
        cout << *iter <<" ";
    cout << endl;
    cout<<"lt1 : ";
    for(list<int>::iterator iter=lt1.begin(); iter != lt1.end(); ++iter)
        cout << *iter <<" ";
    cout << endl;
    cout<<"lt2 : ";
    for(list<int>::iterator iter=lt2.begin(); iter != lt2.end(); ++iter)
        cout << *iter <<" ";
    cout << endl;
}