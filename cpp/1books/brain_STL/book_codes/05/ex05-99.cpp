#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

void main( )
{
    //vector<typename T, typename Alloc = allocator<T> >
    // vector<int> 와 같음
    vector< int, allocator<int> > v;
    v.push_back( 10 );
    cout << *v.begin() << endl;

    //set<typename T, typename Pred = less< T >, typename Alloc = allocator<T> >
    // set<int> 와 같음
    set< int, less<int>, allocator<int> > s;
    s.insert( 10 );
    cout << *s.begin() << endl;
}