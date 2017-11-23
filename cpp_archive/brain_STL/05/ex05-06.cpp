#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void main( )
{ 
    vector<int> v; 
    v.push_back(10); 
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    list<int> lt;
    lt.push_back(10); 
    lt.push_back(20);
    lt.push_back(30);
    lt.push_back(40);
    lt.push_back(50);

    sort(v.begin(), v.end()); // 정렬 가능(vector는 임의 접근 반복자)
    sort(lt.begin(), lt.end()); // 에러!(list는 양방향 반복자)
}