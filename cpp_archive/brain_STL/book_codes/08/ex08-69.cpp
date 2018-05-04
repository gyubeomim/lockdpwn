#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2;
    v2.push_back(10);
    v2.push_back(20);
    v2.push_back(40);
        
    vector<int> v3;
    v3.push_back(10);
    v3.push_back(20);
    v3.push_back(60);

    if( includes(v1.begin(), v1.end(), v2.begin(), v2.end()) )
        cout <<"v2는 v1의 부분 집합" << endl;
    else 
        cout <<"v2는 v1의 부분 집합 아님" << endl;

    if( includes(v1.begin(), v1.end(), v3.begin(), v3.end()) )
        cout <<"v3는 v1의 부분 집합" << endl;
    else 
        cout <<"v3는 v1의 부분 집합 아님" << endl;

    //정렬 기준을 greater<int> 설정
    sort(v1.begin(), v1.end(), greater<int>());
    sort(v2.begin(), v2.end(), greater<int>());
    //비교 기준을 greater<int> 설정
    if( includes(v1.begin(), v1.end(), v2.begin(), v2.end(), greater<int>()) )
        cout <<"greater정렬 순차열: v2는 v1의 부분 집합" << endl;
}