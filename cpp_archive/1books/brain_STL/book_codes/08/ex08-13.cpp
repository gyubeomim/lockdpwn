#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void Print(int n)
{
    cout << n << " ";
}
void main( )
{  
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);
        
    for_each(v.begin(), v.begin()+2, Print);
    cout << endl;
    for_each(v.begin(), v.begin()+4, Print);
    cout << endl;
    //[v.begin(), v.end()) 구간의 원소 출력
    for_each(v.begin(), v.end(), Print);
    cout << endl;
}
