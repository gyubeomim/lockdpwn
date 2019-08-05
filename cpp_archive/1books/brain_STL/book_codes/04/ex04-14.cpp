#include <iostream>
#include <string>
using namespace std;

template <typename T>
class ObjectInfo
{
    T data;
public:
    ObjectInfo(const T& d):data(d) { }
    void Print( )
    {
        cout <<"타입 : "<< typeid(data).name() << endl;
        cout <<"크기 : "<< sizeof(data) << endl;
        cout <<"값 : "<< data << endl;
        cout <<endl;
    }
};
void main( ) 
{
    ObjectInfo<int> d1(10);
    d1.Print( ); // 객체 정보 출력

    ObjectInfo<double> d2(5.5);
    d2.Print( ); // 객체 정보 출력

    ObjectInfo<string> d3("Hello!");
    d3.Print( ); // 객체 정보 출력
}
