#include <iostream>
#include <list>
using namespace std;

void main( )
{
    list<int> lt1;
    list<int> lt2;

    lt1.push_back(10);
    lt1.push_back(20);
    lt1.push_back(30);
    lt1.push_back(40);
    lt1.push_back(50);

    lt2.push_back(100);
    lt2.push_back(200);
    lt2.push_back(300);
    lt2.push_back(400);
    lt2.push_back(500);
    
    list<int>::iterator iter1;    
    list<int>::iterator iter2;    
    cout << "lt1: ";
    for(iter1 = lt1.begin(); iter1 != lt1.end(); ++iter1)
        cout << *iter1 << ' ';
    cout << endl;

    cout << "lt2: ";
    for(iter2 = lt2.begin(); iter2 != lt2.end(); ++iter2)
        cout << *iter2 << ' ';
    cout <<endl << "=============" << endl;

    iter1 = lt1.begin();
    ++iter1;
    ++iter1; // 30 원소의 위치를 가리킴

    iter2 = lt2.begin();
    ++iter2; // 200 원소의 위치를 가리킴

    //iter1이 가리키는 위치에 iter2가 가리키는 위치의 lt2의 원소를 잘라 붙임
    lt1.splice(iter1, lt2, iter2); 

    cout << "lt1: ";
    for(iter1 = lt1.begin(); iter1 != lt1.end(); ++iter1)
        cout << *iter1 << ' ';
    cout << endl;

    cout << "lt2: ";
    for(iter2 = lt2.begin(); iter2 != lt2.end(); ++iter2)
        cout << *iter2 << ' ';
    cout <<endl << "=============" << endl;

    //lt1.end()가 가리키는 위치에 순차열 [lt2.begin(), lt2.end())를 잘라 붙임
    lt1.splice(lt1.end(), lt2, lt2.begin(), lt2.end());
    
    cout << "lt1: ";
    for(iter1 = lt1.begin(); iter1 != lt1.end(); ++iter1)
        cout << *iter1 << ' ';
    cout << endl;

    cout << "lt2: ";
    for(iter2 = lt2.begin(); iter2 != lt2.end(); ++iter2)
        cout << *iter2 << ' ';
    cout <<endl;
}