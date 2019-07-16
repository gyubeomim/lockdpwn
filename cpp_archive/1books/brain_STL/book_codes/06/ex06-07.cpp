#include <iostream>
#include <vector>
using namespace std;

void main( )
{ 
    vector<int> v1(5); //기본값 0으로 초기화된 size가 5인 컨테이너
    for(vector<int>::size_type i = 0 ; i < v1.size() ; ++i)
        cout << v1[i] << " ";   
    cout << endl;

    vector<int> v2(5,0); //지정값 0으로 초기화된 size가 5인 컨테이너    
    for(vector<int>::size_type i = 0 ; i < v2.size() ; ++i)
        cout << v2[i] << " ";   
    cout << endl;

    vector<int> v3(5,10); //지정값 10으로 초기화된 size가 5인 컨테이너    
    for(vector<int>::size_type i = 0 ; i < v3.size() ; ++i)
        cout << v3[i] << " ";   
    cout << endl;
}