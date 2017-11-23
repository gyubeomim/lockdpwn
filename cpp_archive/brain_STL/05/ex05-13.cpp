#include <iostream>
#include <functional> //not2 »ç¿ë
using namespace std;

void main( )
{
    cout << less<int>()(10, 20) << endl; //ÀÓ½Ã less °´Ã¼·Î ºñ±³
    cout << less<int>()(20, 20) << endl;    
    cout << less<int>()(20, 10) << endl;
    cout << "==============" <<endl;
    cout << not2( less<int>() )(10, 20) << endl;// ÀÓ½Ã °´Ã¼ less¿¡ not2 ¾î´ðÅÍ Àû¿ë
    cout << not2( less<int>() )(20, 20) << endl;    
    cout << not2( less<int>() )(20, 10) << endl;
    cout << endl;

    less<int> l;
    cout << l(10, 20) << endl; // less °´Ã¼ l·Î ºñ±³    
    cout << l(20, 20) << endl;    
    cout << l(20, 10) << endl;
    cout << "==============" <<endl;
    cout << not2( l )(10, 20) << endl; // less °´Ã¼ l¿¡ not2 ¾î´ðÅÍ Àû¿ë
    cout << not2( l )(20, 20) << endl;
    cout << not2( l )(20, 10) << endl;
}