#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct TEST{
    double t1;
    double t2;
    double t3;  
};

int main() {
    TEST t;

    for(int i=0; i<2; i++) {
        stringstream ss;
        ss << 't' << i;
        string var_ = ss.str();

        t.var_ = i*10;
        cout << t.var_ << endl;
    }

    return 0;
}