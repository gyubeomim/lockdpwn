/*
  c++ stl p302 algo ==> count() 알고리즘을 처음 사용한 예제
*/
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
    vector<int> v;

    v.push_back(10);    v.push_back(20);
    v.push_back(30);    v.push_back(40);
    v.push_back(30);    v.push_back(50);
    v.push_back(10);    v.push_back(20);
    v.push_back(30);    v.push_back(40);
    v.push_back(30);    v.push_back(50);
    v.push_back(10);    v.push_back(20);
    v.push_back(30);    v.push_back(40);
    v.push_back(30);    v.push_back(50);
    v.push_back(10);    v.push_back(20);
    v.push_back(30);    v.push_back(40);
    v.push_back(30);    v.push_back(50);


    for(vector<int>::size_type i = 0 ; i < v.size() ; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;


    // count() 알고리즘을 사용한 예제
    int n = count(v.begin(), v.end(), 30);
    cout << "30의 개수는: " << n << endl;



    return 0;
}
