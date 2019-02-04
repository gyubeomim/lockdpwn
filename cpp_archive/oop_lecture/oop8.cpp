#include <iostream>
using namespace std;

class MyVector
{
	int *p;
	int size;

	public:
	MyVector(int n = 100)
	{
		p = new int[n];
		size = n;
	}
	~MyVector()
	{
		delete[] p;
	}


};

void f(char c = ' ', int line = 1)
{
	for (int i =0 ; i < line; i++) 
	{
		for (int j =0; j < 10; j++) 
		{
			cout << c;
		}
		cout << endl;
	}
}

void fillLine(int n=25, char c='*')
{
	for (int i = 0; i < n; i++) 
	{
		cout << c;
	}
	cout << endl;
}

int main(int argc, const char *argv[])
{
	f();
	f('%');
	f('@', 5);

	fillLine();

	return 0;
}













