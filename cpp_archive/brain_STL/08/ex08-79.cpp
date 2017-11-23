#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int Plus(int left, int right)
{
    return left+right;
}
int Minus(int left, int right)
{
    return left-right;
}
void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2;
    v2.push_back(2);
    v2.push_back(2);
    v2.push_back(2);
    v2.push_back(2);
    v2.push_back(2);

    // 0 + 10-2 + 20-2 + 30-2 + 40-2 + 50-2 사용자 함수 사용
    cout << inner_product(v1.begin(), v1.end(), v2.begin(), 0, Plus, Minus) << endl;
    // 0 + 10-2 + 20-2 + 30-2 + 40-2 + 50-2 STL 함수자 사용
    cout << inner_product(v1.begin(), v1.end(), v2.begin(), 0, plus<int>(), minus<int>()) << endl;
}