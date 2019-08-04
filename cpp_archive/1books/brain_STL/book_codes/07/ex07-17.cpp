#include <iostream>
#include <map>
#include <string>
using namespace std;

void main( )
{  
    // greater 정렬 기준의 key:int, value:string 타입의 컨테니어 m 생성.
    map<int, string, greater<int> > m;
    
    m[5] = "five"; // 원소 추가
    m[3] = "three";
    m[8] = "eight";
    m[4] = "four";
    m[1] = "one";
    m[7] = "seven";
    m[9] = "nine";

    map<int,string, greater<int> >::iterator iter;
    for( iter = m.begin() ; iter != m.end() ; ++iter)
        cout <<"("<< iter->first <<',' << iter->second <<")" <<" ";
    cout << endl;


    cout << m[9] <<" "; //key와 매핑된 value를 출력합니다.
    cout << m[8] <<" ";
    cout << m[7] <<" ";
    cout << m[5] <<" ";
    cout << m[4] <<" ";
    cout << m[3] <<" ";
    cout << m[1] <<endl;
}