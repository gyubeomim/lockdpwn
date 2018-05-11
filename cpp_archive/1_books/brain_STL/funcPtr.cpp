/*
  c++ stl p70 함수 포인터를 활용해 콜백함수를 구현하는 코드
*/
#include <iostream>

using namespace std;

////////////서버//////////////////////
void For_each(int *begin, int *end, void(*pf)(int))
{
    while(begin != end)
        {
            //cout<<"@@"<<*begin<<endl;
            //cout<<"!!"<<begin<<endl;
            pf(*begin++);
            //cout<<endl;
        }
}

/////////클라이언트///////////////////
void Print1(int n)
{
    cout<<n<<' ';
}

void Print2(int n)
{
    cout<<n*n<<" ";
}

void Print3(int n)
{
    cout<<"int: "<<n<<endl;
}

int main()
{
    int arr[5] = {10,20,30,40,50};

    For_each(arr,arr+5,Print1);
    cout<<endl<<endl;

    For_each(arr,arr+5,Print2);
    cout<<endl<<endl;

    For_each(arr,arr+5,Print3);
}
