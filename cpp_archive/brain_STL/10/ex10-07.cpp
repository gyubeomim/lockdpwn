#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

void main() 
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2; // size: 0인 vector 생성
    //copy(v1.begin(), v1.end(), v2.begin() ); //에러!
    //insert_iterator<vector<int> > insert(v2, v2.begin());
    //copy(v1.begin(), v1.end(), insert ); 객체 생성 후 호출
    copy(v1.begin(), v1.end(), inserter<vector<int> >(v2, v2.begin()) );

    cout<<"v1 : ";
    for(vector<int>::iterator iter=v1.begin(); iter != v1.end(); ++iter)
        cout << *iter <<" ";
    cout << endl;
    cout<<"v2 : ";
    for(vector<int>::iterator iter=v2.begin(); iter != v2.end(); ++iter)
        cout << *iter <<" ";
    cout << endl;
}