#include <iostream>
using namespace std;

class Array
{
    int *arr;
    int size;
    int capacity;
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
};

void main( )
{
    Array ar(10);

    ar.Add( 10 );
    ar.Add( 20 );
    ar.Add( 30 );
    for( int i = 0 ; i < ar.Size() ; i++)
        cout << ar[i] << endl; // ar.operator[](i) 와 같습니다.
}