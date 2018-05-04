#include <iostream>
#include <set>
using namespace std;

void main( )
{ 
    multiset<int> ms;
    
    ms.insert(50);
    ms.insert(30);
    ms.insert(80);
    ms.insert(80); // 80 중복
    ms.insert(30); // 30 중복
    ms.insert(70); 
    ms.insert(10);

    multiset<int>::iterator iter;    
    for( iter = ms.begin() ; iter != ms.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;

    cout <<"30 원소의 개수: " << ms.count(30) << endl; // 30 원소의 개수

    iter = ms.find(30); // 30 첫 번째 원소의 반복자
    cout << "iter: " << *iter<< endl;

    multiset<int>::iterator lower_iter;    
    multiset<int>::iterator upper_iter;    

    lower_iter = ms.lower_bound(30); // 30 순차열의 시작 반복자
    upper_iter = ms.upper_bound(30); // 30 순차열의 끝 표시 반복자
    cout <<"lower_iter: " << *lower_iter <<",  " <<"upper_iter: " << *upper_iter << endl;

    cout <<"구간 [lower_iter, upper_iter)의 순차열: " ;
    for( iter = lower_iter ; iter != upper_iter ; ++iter)
        cout << *iter << " ";
    cout << endl;
}
