#include <iostream>
#include <algorithm> // for_each() 알고리즘(서버)을 사용하기 위한 헤더
using namespace std;
/////// 클라이언트 /////////
void Print1(int n) // 공백을 이용하여 원소를 출력
{
    cout << n <<' ';
}
void Print2(int n) // 각 원소를 제곱하여 출력
{
    cout << n*n <<" ";
}
void Print3(int n) // 문자열과 endl을 이용하여 원소를 출력
{
    cout <<"정수 : "<< n <<endl;
}
void main( )
{
    int arr[5] = {10,20,30,40,50};
    
    for_each(arr, arr+5, Print1); // Print1() 콜백 함수의 주소를 전달
    cout << endl << endl;
    for_each(arr, arr+5, Print2); // Print2() 콜백 함수의 주소를 전달
    cout << endl << endl;
    for_each(arr, arr+5, Print3); // Print3() 콜백 함수의 주소를 전달
}