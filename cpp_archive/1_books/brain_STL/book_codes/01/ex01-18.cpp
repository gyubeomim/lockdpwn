#include <iostream>
using namespace std;

class Array
{
    int *arr;
    int size;
    int capacity;
    // 복사 함수 생략(복사 생성자,복사 대입 연산자)
public:
    Array(int cap=100):arr(0),size(0),capacity(cap)
    {
        arr = new int[capacity];
    }
    ~Array()
    { 
        delete [] arr;
    }
    void Add( int data)
    {
        if( size < capacity )
            arr[size++] = data;
    }   
    int Size( ) const
    {
        return size;
    }
    int operator[](int idx) const
    {
        return arr[idx];
    } 
    int& operator[](int idx)
    {
        return arr[idx];
    }
};

void main( )
{
    Array ar(10);
    ar.Add( 10 );
    ar.Add( 20 );
    ar.Add( 30 );

    
    cout << ar[0] << endl; // ar.operator[](int) 를 호출합니다.
    cout << endl;

    const Array& ar2 = ar;
    cout << ar2[0] << endl; // ar.operator[](int) const 를 호출합니다.
    cout << endl;

    ar[0] = 100; // ar.operator[](int) 를 호출합니다.
    //ar[1] = 100; 에러! 상수 객체(값)를 리턴하므로 대입할 수 없습니다.
}