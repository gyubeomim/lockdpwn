#include <iostream>
#include <map>
using namespace std;

void main( )
{  
    map<int,int> m;
    
    m[5] = 100;
    m[3] = 100;
    m[8] = 30;
    m[4] = 40;
    m[1] = 70;
    m[7] = 100;
    m[9] = 50;

    map<int,int>::iterator iter;
    for( iter = m.begin() ; iter != m.end() ; ++iter)
        cout <<"("<< iter->first <<',' << iter->second <<")" <<" ";
    cout << endl;

    iter = m.find( 5 );
    if( iter != m.end() )
        cout << "key 5에 매핑된 value: " << iter->second << endl;

    map<int,int>::iterator lower_iter;
    map<int,int>::iterator upper_iter;
    lower_iter = m.lower_bound(5);
    upper_iter = m.upper_bound(5);

    cout <<"구간 [lower_iter, upper_iter)의 순차열: "; 
    for( iter = lower_iter ; iter != upper_iter ; ++iter)
        cout << "(" << iter->first <<',' << iter->second <<") ";
    cout << endl;

    pair<map<int,int>::iterator, map<int,int>::iterator> iter_pair;
    iter_pair = m.equal_range(5);

    cout <<"구간 [iter_pair.first, iter_pair.second)의 순차열: "; 
    for( iter = iter_pair.first ; iter != iter_pair.second ; ++iter)
        cout << "(" << iter->first <<',' << iter->second <<") ";
    cout << endl;
}