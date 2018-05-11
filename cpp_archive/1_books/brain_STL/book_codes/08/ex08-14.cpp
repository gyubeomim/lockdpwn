#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class PrintFunctor
{
    char fmt;
public:
    explicit PrintFunctor(char c = ' '):fmt(c) { }
    void operator ()(int n) const
    {
        cout << n << fmt;
    }
};
void main( )
{  
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);
        
    for_each(v.begin(), v.end(), PrintFunctor()); // 원소의 구분을 ' '로
    cout << endl;
    for_each(v.begin(), v.end(), PrintFunctor(','));// 원소의 구분을 ','로
    cout << endl;
    for_each(v.begin(), v.end(), PrintFunctor('\n'));// 원소의 구분을 '\n'로
    cout << endl;
}