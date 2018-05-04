 #include <iostream>
#include <map>
using namespace std;

void main( )
{  
    //key, value 모두 정수형인 컨테이너 생성
    //기본 정렬 기준 less
    map<int,int> m;
    
    m.insert( pair<int,int>(5,100) ); // 임시 pair 객체 생성 후 저장
    m.insert( pair<int,int>(3,100) );
    m.insert( pair<int,int>(8,30) );
    m.insert( pair<int,int>(4,40) );
    m.insert( pair<int,int>(1,70) );
    m.insert( pair<int,int>(7,100) );
    
    pair<int, int> pr(9,50);
    m.insert( pr ); // pr 객체 생성 후 저장

    map<int,int>::iterator iter;    
    for( iter = m.begin() ; iter != m.end() ; ++iter)
        cout <<"("<< (*iter).first <<',' << (*iter).second <<")" <<" ";
    cout << endl;

    // 반복자는 -> 연산자가 연산자 오버로딩되어 있으므로 
    //포인터처럼 멤버를 -> 연산자로 접근할 수 있습니다. 
    for( iter = m.begin() ; iter != m.end() ; ++iter)
        cout <<"("<< iter->first <<',' << iter->second <<")" <<" ";
    cout << endl;
}