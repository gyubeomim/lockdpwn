#include <iostream>
#include <vector>
#include <list>
using namespace std;

void main( )
{
    vector<int> v;
    list<int> lt;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    lt.push_back(10);
    lt.push_back(20);
    lt.push_back(30);
    lt.push_back(40);
    lt.push_back(50);
    
    vector<int>::iterator viter = v.begin();
    ++viter; // 20원소를 가리킴
    list<int>::iterator liter = lt.begin();
    ++liter; // 20원소를 가리킴

    viter = v.insert(viter, 600); // v의 두 번째 요소로 삽입
    liter = lt.insert(liter, 600); // lt의 두 번째 요소로 삽입

    cout <<"vector: " << *viter << endl;
    cout <<"list: " << *liter << endl;

    cout << "vector : ";
    for(viter = v.begin(); viter != v.end(); ++viter)
        cout << *viter << ' ';
    cout << endl;    
    
    cout << "list : ";
    for(liter = lt.begin(); liter != lt.end(); ++liter)
        cout << *liter << ' ';
    cout << endl;
}
