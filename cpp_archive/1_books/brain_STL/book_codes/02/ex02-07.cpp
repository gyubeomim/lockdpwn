#include <iostream>
using namespace std;
void Client();

//////// 서버 /////////////
void PrintHello( )
{
    cout << "Hello!" << endl;
    Client(); //서버에서 클라이언트 코드 호출
}
/////// 클라이언트 /////////
void Client( )
{
    cout << "난 client" << endl;
}
void main( )
{
    PrintHello( ); //서버 코드 호출
}