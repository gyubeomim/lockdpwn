/*
  c++ stl p113 template 사용법 예제 코드
*/
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

template<typename T>
class ObjectInfo
{
  T data;

 public:
  ObjectInfo(const T& d)   : data(d)
  {}

  void Print()
  {
    cout<<"타입 : "<<typeid(data).name() << endl;
    cout<<"크기 : "<<sizeof(data)<<endl;
    cout<<"값 : " << data << endl;
  }
};

template<>
class ObjectInfo<string>
{
  string data;

 public:
  ObjectInfo(const string& d)   : data(d)
  {  }

  void Print()
  {
    cout<<"타입 : "<<"string"<<endl;
    cout<<"문자열 길이 : " << data.size() << endl;
    cout<<"값 : "<<data <<endl;
  }
};

int main()
{
  ObjectInfo<int> d1(10);
  d1.Print();

  cout<<"-----------야스 야스 야스"<<endl;

  ObjectInfo<double> d2(5.5);
  d2.Print();
  cout<<"----------야스 야스 야스"<<endl;
  
  ObjectInfo<string> d3("Hello!");
  d3.Print();

  cout<<"---------야스 야스 야스"<<endl;

  return 0;
}
