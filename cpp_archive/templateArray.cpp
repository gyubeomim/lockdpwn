#include <iostream>

using namespace std;

template<typename T=int, int capT=100>
class Array
{
  T *buf;
  int size;
  int capacity;

 public:

  explicit Array(int cap= capT) : buf(0), size(0), capacity(cap)
  {
    buf = new T[capacity];
  }

  ~Array()
  {
    delete []buf;
  }

  void Add(T data)
  {
    buf[size++] = data;
  }

  T operator[](int idx) const
  {
    return buf[idx];
  }

  int getSize() const
  {
    return size;
  }
    
};



int main()
{
  Array<> iarr;    // 템플릿 디폴트 값 사용: Array<int, 100>

  iarr.Add(10);
  iarr.Add(20);
  iarr.Add(30);

  for(int i = 0; i<iarr.getSize() ; ++i)
  {
    cout<<iarr[i] << " ";
  }

  cout << endl;

  Array<double> darr;   // double형 템플릿

  darr.Add(10.1);
  darr.Add(10.2);
  darr.Add(10.3);

  for (int i = 0 ; i< darr.getSize(); ++i)
  {
    cout<<darr[i]<<" ";
  }

  cout<< endl;


  Array<string,10> sarr;   // <string,10>형 템플릿
  sarr.Add("ed");
  sarr.Add("ward");
  sarr.Add("Is Awesome");

  for(int i = 0 ; i<sarr.getSize() ; ++i)
  {
    cout<<sarr[i]<< " ";
  }

  cout<<endl;
    
    
}
