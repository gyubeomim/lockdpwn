#include <iostream>
using namespace std;

template <typename T>
void Swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
void main( )
{
    int n1 = 10, n2 = 20;
    double d1 = 1.1, d2 = 2.2;

    cout << n1 <<", " << n2 << endl;
    Swap(n1, n2);
    cout << n1 <<", " << n2 << endl;
    cout << endl;

    cout << d1 <<", " << d2 << endl;
    Swap(d1, d2);
    cout << d1 <<", " << d2 << endl;
}
