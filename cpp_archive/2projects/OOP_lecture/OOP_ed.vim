# coding: utf-8

-----------------------------------------------------------------------------------


-----------------------------------------------------------------------------------


-----------------------------------------------------------------------------------


-----------------------------------------------------------------------------------
170605_월

# 예외처리 
	try{
		... throw 1;
			throw "0으로 나누는 예외발생";
			throw 0;
	}
	catch(int e){
		cout << e << endl;
	}
	catch(char* e){
		cout << e << endl;
	}



# 예외처리 클래스 생성


# 이름 규칙, Name Mangling 
	# c++ : int f(int x, int y) ==> ?f@@YAXH@Z
	# c : int f(int x, int y) ==> _f


	# extern "C" 구문 사용한다

		extern "C" int f(int x, int y)
	

		extern "C"{
			int f(int x, int y);
			void g();
			char s(int []);
		}


		extern "C"{
			#include "mycfunction.h"
		}









-----------------------------------------------------------------------------------
170530_화

# 텍스트 파일의 라인 단위 읽기
	istream getline(char* line, int n)
	getline(ifstrea fin, string line)


	# 예제들 내용 좋다 한번 보기




# 바이너리 IO 모드
	ios::binary
	
	# 문자, 바이트 단위 파일 입출력 함수
		get()
		put()

	# 블록 단위 파일 입출력 함수 
		istream& read(char* s, int n)    // n개 바이트를 배열 s에 읽어들임
		ostream& write(char* s, int n)
		int gcount()


		

# 텍스트 IO <==> 바이너리 IO의 확실한 차이점
	# 파일의 끝을 처리하는 방법에는 차이가 없다
	# 개행문자 '\n' 를 읽고 쓸 때 서로 다르게 작동한다



# 스트림 상태 검사
	# 스트림 상태 
		failbit
		eofbit
		badbit

	


# 임의 접근과 파일 포인터
	istream& seekg(streampos pos)
	istream& seekg(streamoff offset, ios::seekdir seekbase)

	ostream& seekp(streampos pos)
	ostream& seekp(streamoff offset, ios::seekdir seekbase)

	streampos tellg()
	streampos tellp()

	# seekbase 옵션 3가지
		ios::beg
		ios::cur
		ios::end



long getFileSize(ifstream& fin){
	fin.seekg(0, ios::end);
	long length = fin.tellg();
	return length;
}
	
int main(){
	char *file = "c:\\windows\\system.ini";

	ifstream fin(file);
	if(!fin){
		cout << file << " open error " << endl;
		return 0;
	}

	cout << file << " size is : " << getFileSize(fin);
	fin.close();
}








-----------------------------------------------------------------------------------
170529_월

# 텍스트 파일 <==> 바이너리 파일

	# CRLF
		# Carriage Return Line Feed 
		# \x0D\x0A
		# \r\n


	# 바이너리 파일
		# 각종 실행파일들


	# hwp 파일은 바이너리 파일이다 
		# 텍스트 정보를 포함한 바이너리 파일이다


	# typedef basic_ifstream<char, char_traits<char>> ifstream;


	# #include <fstream> 이 필요하다



	# 파일 입출력 모드 
		# 텍스트 I/O     <==>     바이너리 I/O
		# 개행문자 \n를 다루는데 차이가 있다



	# 파일 모드 file mode
		# ios::in, ios::out, ios::app; ios::binary



	# pdf 자료 예제 12-3 한번 보기!
		# 실제 바이트 수가 219 ==> 206으로 표시된다. \r는 전부 생략됨


	# get() 과 EOF 
		# 파일의 끝을 인지하는 방법










!! 6/13 화 저녁 7시 기말고사 시험본다. 공학관 228호
	! 다음주 목요일부터 기말고사 기간이다





-----------------------------------------------------------------------------------
170523_화

# 포맷 입출력
	# 포맷 플래그 : 입출력 스트림에서 입출력 형식을 지정하기 위한 플래그
		long setf(long flags)
		long unsetf(long flags)


	# 포맷 함수
		int width(int minWidth)
		char fill(char cFill)
		int precision(int np)


	# 조작자 manipulator
		# 매개변수 있는 조작자 vs 매개변수 없는 조작자
			cout << hex << showbase << 30 << endl;
			cout << dec << showpos << 100 << endl;

			#include <iomanip>
			cout << setw(10) << setfill('^') << "Hello" << endl;




# 삽입 연산자 << 
	# 삽입 연산자의 실행 과정

	# 사용자 삽입 연산자 만들기

	class Point{
		...
		friend ostream& operator << (ostream& stream, Point a);
	};

	// couut << a << b 같이 여러번 >>를 사용하는 경우에 대비해 istream& 반환타입을 설정한다
	ostream& operator << (ostream& stream, Point a){
		stream << "(" << a.x << "," << a.y << ")";
		return stream;
	};

	Point p(3,4);
	cout << p << endl;

	Point q(1,100), r(2,200);
	cout << q << r << endl;

	


# 추출 연산자 >>
	class Point{
		...
		friend istream& operator >> (istream &ins, Point &a);
	}; 

	// cin >> a >> b 같이 여러번 >>를 사용하는 경우에 대비해 istream& 반환타입을 설정한다
	istream& operator >> (istream& ins, Point& a){
		...

		return ins
	};

	Point p;
	cin >> p;
	cout << p;




# 사용자 정의 조작자 만들기
	ostream& fivestar(ostream& outs){
		return otus << "*****";
	}

	istream& question(istream& ins){
		cout << " blah blah ";
		return ins;
	}









-----------------------------------------------------------------------------------
170522_월

# 입출력 스트림

	# c++ 입출력 스트림은 버퍼를 가진다
		# 키 입력용 스트림 버퍼
		# 스크린 출력용 스트림 버퍼



	# 구 표준 c++ 입출력 라이브러리의 단점
		# char ch;
		  cin >> ch;
		한글을 입력하지 못한다


	# iostream
		# cin :
		# cout :
		# cerr :
		# clog : 


	# ostream
		ostream& flush()
		ostream& put(char ch)
		ostream& write(char *str, int n)



	# istream
		int get()
		istream& get(char& ch)

		istream& get(char *s, int n)

		istream& get(char *s, int n, char delim='\n')
		istream& getline(char *s, int n, char delim='\n')

		istream& ignore(int n=1, int delim=EOF)
		int gcount()












-----------------------------------------------------------------------------------
170516_화

# cout << a << b << c    의 실행순서 이해하기!


# 2개의 제니릭 타입을 가진 클래스 만들기

template <class T1, class T2>
class GClass{
	...
};



# 표준 템플릿 라이브러리 STL
	
	# vector 
	# deque
	# list
	# set
	# map
	# stack
	# queue


	# iterator
	# const_iterator
	# reverse_iterator

	# copy
	# equal
	# find
	# max
	# ...



	# vector containor
		vector<int> v;
		
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);

		for(int i = 0; i < v.size(); i++)
			cout << v[i] << ' ';
		cout << endl;

		...
		vector<string> sv;
		string name;
	


	
	# iterator : 컨테이너의 원소를 가르키는 포인터

		vector<int> v;
		vector<int>::iterator it;
		it = v.begin();

		it++;

		it = v.erase(it);
		it = v.end();



	# algorithm

		sort(v.begin(), v.end());

















-----------------------------------------------------------------------------------
170515_월

# 일반화와 템플릿	

template <class T>
void myswap(T &a, T &b){
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}
# 단 (int a, double b) 같은 구문은 처리하지 못한다


template <class T1, class T2>
void mcopy(T1 src, T2 dest[], int n){
	for(int i = 0 ; i < n ; i++)
		dest[i] = (T2)src[i];
}

int main(){
	int x[] = {1,2,3,4,5};
	double d[5];
	char c[5] = {'H','e','l','l','o'};
	char d[5];

	mcopy(..)
	...
}



template <class T>
void print(T array[], int n){
	for(int i =0 ; i< n ; i++)
		cout << array[i] << '\t';
	cout << endl;
}


void print(char array[], int n){
	for(int i =0; i < n; i++)
		cout << (int)array[i] << '\t';
	cout << endl;
}



# 제네릭, 템플릿 클래스 만들기


template <class T>
class MyStack {
	int tos;
	T data[100];

public:
	MyStack();
	void push(T element);
	T pop();
};

template <class T>
T MyStack<T>::pop(){
	...
}

template<class T>
void MyStack<T>::push(T element){
	...
}


int main(){
	MyStack<int> iStack;
	MyStack<double> dStack;  // 이와 같이 선언해준다
}



# 제네릭 스택의 타입을 포인터나 클래스로 구체화할 수 있다 

class Point{
	int x,y,;

public:
	Point(int x =0 , int y =0) { this->x = x, this->y = y; }
	void show() { cout << '(' << x << ',' << y << ')' << endl;
};











-----------------------------------------------------------------------------------
170508_월

# 중간고사 시험지 체크
	#  95 + 5점




$$ p456 6,7번 문제   
	$ 5/23(화)까지 과제





-----------------------------------------------------------------------------------
170502_화

# 가상함수를 가진 기본클래스의 목적
	


# 가상함수 오버라이딩



# 추상클래스와 순수가상함수

class Shape{                           // 추상클래스
	public:
		virtual void draw() = 0;
};



class Circle : public Shape{            // 추상클래스
	public:
		string toString() { return "Circle 객체"; }
};



class Circle2 : public Shape{           // 추상클래스 아님
	public:
		virtual void draw(){
			cout << "circle";
		}
		string toString() { return "Circle 객체"; }
};

















-----------------------------------------------------------------------------------
170501_월

# 가상함수와 추상클래스
	# Virtual Function  &  Function Overriding
		# 오버로딩과 오버라이딩의 차이점
	    	Overloading  <==>  Overriding

		# Overriding의 목적 :

		# 파생클래스의 virtual 키워드는 생략가능하다

		# 동적바인딩
			# 실행시간까지 함수의 바인딩을 미루는것
			# virtual 함수의 특성

		# 범위지정연산자(::)
			# 정적바인딩을 호출한다. 
			# 기본클래스의 가상함수를 사용하고 싶을 때 사용한다



# 가상소멸자
	ex) virtual ~Base();
	    virtual ~Derived();

		Base *p = new Derived();
		delete p;

	# ~Base() 소멸자 호출 --> ~Derived() 실행 --> ~Base() 실행
	# 복잡한 상속관계에서 소멸자 오류발생을 막을 수 있다		









$ 중간고사 점검
	$ p261 10번문제(중간고사 16번문제) : 문제가 약간 애매해서 전부 맞게 처리해줬다



-----------------------------------------------------------------------------------
170418_화

# 페르마의 마지막 정리 
	# 페르마가 자신의 책에 마지막장에 x^n + y^n = z^n 의 증명을 풀었으나 용지가 없어서 싣지는 않겠다고 함
	# 350년정도 된 문제
	# 앤드류 와일스에 의해 증명되었다





$ 중간고사 25 화 저녁 7시 공학관별관 217호 2시간 


-----------------------------------------------------------------------------------
170417_월

# 8장 고고


# 상속과 객체 포인터
	# 업-캐스팅 up-casting
		# 파생클래스 포인터가 기본클래스 포인터에 치환되는 것

	# 다운-캐스팅 down-casting
		# 기본클래스 포인터가 파생클래스 포인터에 치환되는 것


	# protected 멤버에 대한 접근





# pdf 질문 2개! 잘 보기
	# 상속관계의 생성자와 소멸자의 실행
	


-----------------------------------------------------------------------------------
170411_화

!! 4/25(화) 저녁 7시에 시험본다 
	! 공학관 별관 217호








-----------------------------------------------------------------------------------
170410_월


# 7장 프렌드와 연산자 중복

	# 프렌드의 의미

	# 연산자중복 operator overide

		# c++의 다형성 성질을 가진다
		# 반드시 클래스와 관계를 가진다

	ex) 
		class Power
		{
			int kick;
			int punch;
		public:
			Power(int kick = 0, int punch =0)
			{
				this->kick = kick;
				this->punch = punch;
			}
			Power operator+(Power op2);
			Power operator+=(Power op2);
		};

		// 연산자중복
		Power Power::operator(Power op2)
		{
			Power tmp;
			tmp.kick = this->kick + op2.kick;
			tmp.punch = this->punch + op2.punch;
			return tmp;
		}

		# c = a+b 의 경우 --> 컴파일러는 c = a.+(b) 로 해석한다
		  c = a+=b 구문 오류 없다!
		  






$$ 5장 과제 : p305 실습 2
	$ 5/2 (화)까지 4장 문제랑 같이 제출하기


!! 중간고사는 7장까지
	! 개념을 잘 파악하기
	! 문제는 20문제 
		! 4지선다, 코딩 내용을 분석하기, 코딩을 채우는 내용 등등

	! 5/2일(화) 시험 2시간






-----------------------------------------------------------------------------------
170403_월

# 함수 오버라이딩
	# 파라미터가 달라야 한다

	int sum(int a, int b)
	double sum(double a, double b)

	int big(int a, int b)
	int big(int a[], int size)



# 디폴트 매개변수
	int sum(int a = 10, int b = 20)










-----------------------------------------------------------------------------------
170328_화

# 얕은 복사와 깊은 복사
# 복사 생성자

	# 얕은 복사
		Circle::Circle(Circle& c)  // 복사 생성자
		{
			this->radius = c.radius;
			cout << "복사 생성자 실행 radius = " << radius << endl;
		}

	# 깊은 복사
		Person::Person(Person& person)  // 복사 생성자 
		{
			this->id = person.id; 					// id 값 복사
			int len = strlen(person.name);			// name의 문자 개수
			this->name = new char [len+1]; 			// name을 위한 공간 핟당
			strcpy(this->name, person.name); 		// name의 문자열 복사
			cout << "복사 생성자 실행. 원본 객체의 이름 " << this->name << endl;
		}




	$$ p206 4번 문제 풀어보기
		$ 2주 뒤에 제출하기 4/11(화)까지









-----------------------------------------------------------------------------------
170327_월

# 값에 의한 호출 <==> 주소에 의한 호출
	void swap(int a, int b)
	void swap(int *a, int *b)


# 객체 치환 및 객체 리턴
	Circle getCircle()
	{
		Circle tmp(30);
		return tmp;
	}


# 참조자 &
	# 주로 call by reference를 위해 사용한다
	void increaseCircle(Circle &c)
	{
		int r = c.getRadius();
		c.setRadius(r+1);
	}


	# 참조 리턴
		char& find(char s[], int index)
		{
			return s[index];
		}

		int main()
		{
			char name[] = "Mike";
			cout << name << endl;
			
			find(name,0) = 'S';    // 이런 문법이 가능하다

			char& ref = find(name,2);
			ref = 't';
			cout << name << endl;
		}








-----------------------------------------------------------------------------------
170321_화

# 1024크기 만큼 메모리 누수 발생한다
	char n = 'a';
	char *p = new char[1024];
	p = &n;


# this 포인터
	this->radius = radius;
	또는
	return this;



# string 클래스
		#include <string>
		using namespace std;
		string str = "I love ";
		str.append("C++");
	
	# 문자열 복사
		string address("abcdef");
		string copyAddress(address);
	
		char text[] = {'L','o','v','e',',','C','+','+','\0'};
		string title(text);

	# 문자열 --> 숫자 변환
		string s = "123";
		int n = stoi(s);

		string *p = new string("C++");
		cout << *p;
		p->append(" good man");
		delete p;


	# getline() 함수로 string을 입력받는다

	string names[5]; // 문자열 배열 선언
	for(int i=0; i<5; i++) 
	{
		cout << "이름 >> ";
		getline(cin, names[i], '\n');
	}

	string latter = names[0];

	for(int i=1; i<5; i++) 
	{
		if(latter < names[i]) // 사전 순으로 latter 문자열이 앞에 온다면
		{ 
			latter = names[i]; // latter 문자열 변경
		}
	}
	cout << "사전에서 가장 뒤에 나오는 문자열은 " << latter << endl;















-----------------------------------------------------------------------------------
170320_월

# 포인터는 c와 거의 똑같다

# 객체 배열
	Circle circleArray[3]; 
		# 항상 파라미터가없는 생성자가 호출된다


# 동적메모리 할당
	# malloc, free ==> new, delete
	







-----------------------------------------------------------------------------------
170314_화


# 지역객체와 전역객체 
	# 소멸자의 소멸 순서


# 캡슐화
	# 접근지정자
		# private :
		# public :
		# protected :


# inline  인라인 함수
	# 오버헤드를 막을 수 있다 
	# 컴파일러에 의해 함수의 코드가 main에(주로) 삽입된다

inline int odd(int x)
{ ... }




# struct 구조체
	# c언어와 호환성을 위해 그대로 사용한다
	# 클래스와 똑같이 private, public 작성 가능하다
		# 기본 접근지정자는 public이다 (class는 private)

	
# 아래 구문을 이용해 중복호출을 막는다
	#ifndef CIRCLE_H
	#define CIRCLE_H
	...
	#endif




	$ p145 실습문제 4 
	  p147 실습문제 8
	  결과값이 의미하는 건 뭐다
	
	$ 프린트로 2주 뒤 28일_화 까지 제출













-----------------------------------------------------------------------------------
170313_월

# Object Oriented Programming 객체지향 프로그래밍
	# 캡슐화

	# class 클래스
		# 멤버변수
		# 멤버함수



	







-----------------------------------------------------------------------------------
170307_화

# 임베디드 시스템이란
	# 프로그래밍하는 host와 실제 사용할 target이 다르다


# cin.getline() 을 이용해 문자열을 입력받을 수 있다
	
	int main()
	{
		cout << "주소를 입력하세요" << endl;

		char address[100];
		cin.getline(address, 100, '\n');

		cout << "주소는 " << address << " 입니다\n";

		return 0;
	}



# iostream.h 는 구버전 c++의 헤더파일이다




















