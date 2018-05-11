/*
  c++ stl p71 함수 포인터를 활용해 콜백함수를 구현하는 코드 (algorithm 사용)
*/

#include <iostream>
#include <algorithm>


using namespace std;


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

    for_each(arr,arr+5,Print1);
    cout<<endl<<endl;

    
    for_each(arr,arr+5,Print2);
    cout<<endl<<endl;
    
    
    for_each(arr,arr+5,Print3);


    
}
