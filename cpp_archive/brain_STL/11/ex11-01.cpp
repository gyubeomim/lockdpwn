#include <iostream>
#include <stack>
using namespace std;

void main( )
{
    stack<int> st;

    st.push(10);
    st.push(20);
    st.push(30);

    while( !st.empty() )
    {
        cout << st.top() << endl;
        st.pop();
    }
}