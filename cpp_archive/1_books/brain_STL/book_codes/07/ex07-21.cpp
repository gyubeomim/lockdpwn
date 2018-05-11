#include <iostream>
#include <map>
using namespace std;

void main( )
{  
    multimap<int,int> mm;
    
    mm.insert( pair<int,int>(5, 100) );
    mm.insert( pair<int,int>(3, 100) );
    mm.insert( pair<int,int>(8, 30) );
    mm.insert( pair<int,int>(3, 40) );
    mm.insert( pair<int,int>(1, 70) );
    mm.insert( pair<int,int>(7, 100) );
    mm.insert( pair<int,int>(8, 50) );

    multimap<int,int>::iterator lower_iter;
    multimap<int,int>::iterator upper_iter;
    lower_iter = mm.lower_bound(3);
    upper_iter = mm.upper_bound(3);

    cout <<"구간 [lower_iter, upper_iter)의 순차열: "; 
    multimap<int,int>::iterator iter;
    for( iter = lower_iter ; iter != upper_iter ; ++iter)
        cout << "(" << iter->first <<',' << iter->second <<") ";
    cout << endl;

    pair<multimap<int,int>::iterator, multimap<int,int>::iterator> iter_pair;
    iter_pair = mm.equal_range(3);

    cout <<"구간 [iter_pair.first, iter_pair.second)의 순차열: "; 
    for( iter = iter_pair.first ; iter != iter_pair.second ; ++iter)
        cout << "(" << iter->first <<',' << iter->second <<") ";
    cout << endl;
}