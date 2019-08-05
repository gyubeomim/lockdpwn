#include <iostream>
#include <set>
using namespace std;

void main( )
{
    set<int, less<int> > s; // 정렬 기준 less

    // 30과 50의 비교
    cout << (!s.key_comp()(30, 50) && !s.key_comp()(50,30)) << endl; //다르다
    // 30과 30의 비교
    cout << (!s.key_comp()(30, 30) && !s.key_comp()(30,30)) << endl; //같다(equivalence)
}