#include <iostream>
using namespace std;

class Adder
{
    int total;
public:
    explicit Adder(int n=0):total(n) { }        
    int operator( )(int n)
    {
        return total+=n;
    }
};
void main( )
{
    Adder add(0); //초기값 0

    cout << add(10) << endl; //10을 누적=>10
    cout << add(20) << endl; //20을 누적=>30
    cout << add(30) << endl; //30을 누적=>60
}