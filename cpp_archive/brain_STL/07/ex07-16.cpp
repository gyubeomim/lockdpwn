 #include <iostream>
#include <map>
using namespace std;

void main( )
{  
    map<int,int> m;
    
    m[5] = 100; //key 5, value 100의 원소를 m에 삽입한다.
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

    m[5] = 200; //key 5의 value를 200으로 갱신한다.

    for( iter = m.begin() ; iter != m.end() ; ++iter)
        cout <<"("<< iter->first <<',' << iter->second <<")" <<" ";
    cout << endl;
}