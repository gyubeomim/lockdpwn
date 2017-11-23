// c++ stl p39 상수 객체를 반환하는 [] 연산자 오버로딩에 관한 코드 (const형도 따로 연산자오버로딩 선언을 해줘야 한다)

#include <iostream>

using namespace std;


class Array
{
    int *arr;
    int size;
    int capacity;

    public:

    Array(int cap = 100) :arr(0), size(0), capacity(cap)
    {
        arr = new int[capacity];
    }


    ~Array()
    {
        delete []arr;
    }


    void Add(int data)
    {
        if(size < capacity)
            {
                arr[size++] = data;
            }
    }



    int Size() const
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


int main()
{
    Array ar(10);

    ar.Add(10);
    ar.Add(20);
    ar.Add(30);

    cout<<ar[0] <<endl;     // int& operator[](int idx) 를 호출합니다
    cout<<endl;


    const Array& ar2 = ar;
    
    cout<<ar2[0] <<endl;     // int operator[](int idx) const 를 호출합니다
    cout<<endl;



    ar[0] = 100;   // int& operator[](int idx) 를 호출해 해결합니다
    
    // ar2[0] = 100;  에러! int operator[](int idx) const 를 호출해 해결하다가 안됩니다

    return 0;

            
    
}








