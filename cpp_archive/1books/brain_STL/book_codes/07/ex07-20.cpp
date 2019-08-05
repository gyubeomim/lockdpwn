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

    multimap<int,int>::iterator iter;
    for( iter = mm.begin() ; iter != mm.end() ; ++iter)
        cout <<"("<< iter->first <<',' << iter->second <<")" <<" ";
    cout << endl;

    cout << "key 3의 원소의 개수는 " << mm.count(3) << endl;

    iter = mm.find( 3 );
    if( iter != mm.end() )
        cout << "첫 번째 key 3에 매핑된 value: " << iter->second << endl;
}