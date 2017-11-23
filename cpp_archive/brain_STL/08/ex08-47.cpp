#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    cout << "v : " << v[0] <<" " << v[1] <<" " << v[2] << endl;
    cout << next_permutation(v.begin(), v.end()) << endl;;
    cout << "v : " << v[0] <<" " << v[1] <<" " << v[2] << endl;
    cout << next_permutation(v.begin(), v.end()) << endl;;
    cout << "v : " << v[0] <<" " << v[1] <<" " << v[2] << endl;
    cout << next_permutation(v.begin(), v.end()) << endl;;
    cout << "v : " << v[0] <<" " << v[1] <<" " << v[2] << endl;
    cout << next_permutation(v.begin(), v.end()) << endl;;
    cout << "v : " << v[0] <<" " << v[1] <<" " << v[2] << endl;
    cout << next_permutation(v.begin(), v.end()) << endl;;
    cout << "v : " << v[0] <<" " << v[1] <<" " << v[2] << endl;
    // 마지막 순열이므로 next_permutation()은 false 반환
    cout << next_permutation(v.begin(), v.end()) << endl;;
    cout << "v : " << v[0] <<" " << v[1] <<" " << v[2] << endl;
}