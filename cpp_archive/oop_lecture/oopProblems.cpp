
------------------------------------------------------


------------------------------------------------------


------------------------------------------------------


------------------------------------------------------


------------------------------------------------------


------------------------------------------------------


------------------------------------------------------


------------------------------------------------------


------------------------------------------------------


------------------------------------------------------


------------------------------------------------------
/*
 * c++ ==> 객체지향 p559 7, 0 ~ 127까지 ASCII 코드와 hex 값과 해당하는 문자를 일렬로 출력해보는 코드
 */
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, const char *argv[]){
  int c = 0;

  cout << "dec      hexa    char     ";
  cout << "dec      hexa    char     ";
  cout << "dec      hexa    char     ";

  cout << endl;

  cout << "----     ----     ----    ";
  cout << "----     ----     ----    ";
  cout << "----     ----     ----    ";

  cout << endl;

  while(c < 127){
    for(int i = 0; i < 3; i++){
      if(isprint(c))
        cout << std::dec << c << "        " << std::hex << c << "        " << char(c) << "        " ;
      else
        cout << std::dec << c << "        " << std::hex << c << "        " << "." << "        " ;
      c++;
    }
    cout << endl;
  }
  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p507 13, Circle 클래스를 생성하고 vector<Circle*> v; 를 사용해 Circle들의 이름과 반지름을 입력한 다음 원하는 이름의 원들만 삭제할 수 있도록 해본 코드
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Circle {
  string name;
  int radius;

 public:
  Circle() {}
  Circle(int radius, string name){
    this->radius = radius;
    this->name = name;
  }

  void set(int radius, string name){
    this->radius = radius;
    this->name = name;
  }

  double getArea() { return 3.14*radius*radius;}
  string getName() { return name; }
};

// 여기에 생성해주는게 최선인가 -o- 우선 솔루션은 CircleVectorManager 클래스를 생성해서 관리하니 훨씬 코드가 깔끔하지만 우선 이정도 수준으로만 만족해야징
vector<Circle*> v;

void create(){
  int rad;
  string name;
  cout << "생성하고자 하는 원의 반지름과 이름은 >> ";
  cin >> rad >> name;

  // 굳굳.. 이렇게 vector<Circle*>에 값을 넣는군
  v.push_back(new Circle(rad, name));
}

void remove(){
  string name;
  vector<Circle*>::iterator it = v.begin();
  cout << "삭제하고자 하는 원의 이름은 >> ";
  cin >> name;

  while(it != v.end()){
    Circle *p = *it;
    if(p->getName() == name){
      it = v.erase(it);
      delete p;
    }
    else
      it++;
  }
}

void showAll(){
  vector<Circle*>::iterator it;

  for(it=v.begin() ; it != v.end() ; it++){
    Circle* p = *it;
    cout <<	p->getName() << endl;
  }
}

int main(int argc, const char *argv[]){
  int select;
  cout << "원을 삽입하고 삭제하는 프로그램입니다." << endl;

  while(true){
    cout << "삽입:1, 삭제:2, 모두보기:3, 종료:4 >> ";
    cin >> select;

    // case 문 안에는 변수 생성이 안되는 듯하다. 따라서 아래와 같이 함수 호출문으로 바꿨다
    switch(select){
      case 1:
        create();
        break;
      case 2:
        remove();
        break;
      case 3:
        showAll();
        break;
      case 4:
        exit(0);
      default:
        break;
    }
  }
  return 0;
}

------------------------------------------------------
/*
 * c++ ==> 객체지향 p505 11, Book 클래스를 생성해서 vector<Book> v;를 사용해 책을 입고한 다음 검색해보는 코드 
 * */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book {
  int year;
  string title;
  string author;


 public:
  Book() {}

  void set(int year, string title, string author){
    this->year = year;
    this->title = title;
    this->author = author;
  }

  void show() {
    cout << year << "년도, " << title << ", " << author << endl;
  }

  string getAuthor() { return author; }
  int getYear() { return year; }
};


int main(int argc, const char *argv[]){
  Book b;
  vector<Book> v;
  string author;
  string title;
  int year;

  cout << "입고할 책을 입력하세요. 년도에 -1을 입력하면 입고를 종료합니다" << endl;

  while(true){
    cout << "년도>> ";
    cin >> year; cin.ignore();

    if(year == -1) break;

    cout << "책이름>> ";
    getline(cin, title);

    cout << "저자>> ";
    getline(cin, author);

    b.set(year, title, author);
    v.push_back(b);
  }

  cout << "총 입고된 책은 " << v.size() << "권 입니다." << endl;

  string searchAuthor;
  int searchYear;
	
  cout << "검색하고자 하는 저자 이름을 입력하세요>> " ;
  getline(cin, searchAuthor);

  for(int i = 0 ; i < v.size() ; i++){
    Book b2 = v[i];
    if(b2.getAuthor() == searchAuthor){
      b2.show();
    }
  }

  cout << "검색하고자 하는 년도를 입력하세요>> " ;
  cin >> searchYear;
  cin.ignore();

  for(int i = 0 ; i < v.size() ; i++){
    Book b3 = v[i];
    if(b3.getYear() == searchYear){
      b3.show();
    }
  }

  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p504 9, vector를 사용해 값을 입력받으면서 평균을 출력해보는 코드
 * */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

double getMean(vector<int> ve){
  double sum = 0;

  for(vector<int>::iterator iter = ve.begin() ; iter < ve.end() ; iter++){
    sum += *iter;
  }
  return sum / ve.size();
}

int main(int argc, const char *argv[]){
  vector<int> ve;
  int a;

  while(true){
    cout << "정수를 입력하세요 (0을 입력하면 종료)>> ";
    cin >> a;

    if(a == 0) break;

    ve.push_back(a);

    for(int i = 0; i < ve.size(); i++)
      cout << ve.at(i) << " " ;

    cout << endl << "평균 : " << getMean(ve) << endl;

  }


  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p503, bigger() 템플릿 함수에 Circle a, b를 비교할 수 있도록 operator>() 함수를 추가해 두 개의 Circle 객체를 비교한 코드
 * */
#include <iostream>
#include <string>

using namespace std;

class Circle {
  int radius;
 public:
  Circle(int radius=1) { this->radius = radius; }
  int getRadius() { return radius; }
  bool operator>(Circle &c);
};

// 와우.. 굳굳
bool Circle::operator>(Circle &c){
  if(this->radius > c.getRadius())
    return true;

  return false;
}

template<class T>
T bigger(T a, T b){
  if(a > b) return a;
  else return b;
}


int main(int argc, const char *argv[]){
  int a = 20, b = 50, c;
  c = bigger(a, b);

  cout << "20과 50 중 큰 값은 " << c << endl;

  Circle waffle(10), pizza(20), y;
  y = bigger(waffle, pizza);
		
  cout << "waffle과 pizza 중 큰 것의 반지름은 " << y.getRadius() << endl;

  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p502 5, concat 템플릿함수를 사용해 a[]와 b[]을 서로 이어주는 함수를 구현해본 코드
 */
#include <iostream>
#include <string>

using namespace std;

template<typename T>
T *concat(T a[], int sizea, T b[], int sizeb){
  T *con = new T[sizea + sizeb];
  int i = 0;

  for(; i < sizea ; i++){
    con[i] = a[i];
  }

  for(; i < sizea + sizeb ; i++){
    con[i] = b[i - sizea];
  }

  return con;
}

int main(int argc, const char *argv[]){
  int x[] = {1,2,3};
  int y[] = {4,5,6};
  int *z;

  z = concat(x,3,y,3);

  for(int i = 0; i < 6 ; i++){
    cout << z[i] << " ";
  }



  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p501 1,3, 배열을 받아 가장 큰 값을 리턴하는 biggest() 템플릿함수를 만들고 배열을 뒤집는 reverseArray 함수를 만들어 사용해본 코드
 */
#include <iostream>
#include <string>

using namespace std;

template<typename T>
T biggest(T x[], int size){
  T biggest = x[0];

  for(int i = 0; i < size - 1 ; i++){
    if(x[i] < x[i+1])
      biggest = x[i+1];
  }

  return biggest;
}

template<typename T>
void reverseArray(T *x, int size){
  T rev[size] = {0};

  for(int i = 0; i < size ; i++){
    rev[size - 1 - i]	= x[i];
  }

  for(int i = 0; i < size ; i++){
    x[i] = rev[i];
  }
}

int main(int argc, const char *argv[]){
  int x[] = {1, 10, 100, 5, 4};

  cout << biggest(x, 5) << endl;

  reverseArray(x,5);
  for(int i = 0 ; i < 5 ; i++) cout << x[i] << ' ';
  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p458 9, AbstractPrinter 클래스를 상속받는 InkJetPrinter, LaserPrinter를 생성한 뒤 프린터와 용지의 갯수를 입력하면 해당 숫자만큼 프린트해주는 코드
 */
#include <iostream>
#include <string>

using namespace std;

class AbstractPrinter {
	
 protected:
  string model;
  string manufacturer;

 public:
  int availableCount;
  int printedCount;

  AbstractPrinter(string model, string manufacturer, int availableCount)
      : model(model), manufacturer(manufacturer), availableCount(availableCount)
  {}
  virtual void print(int pages) = 0;
  virtual void show() = 0;

};


class InkJetPrinter : public AbstractPrinter {

 public:
  int availableInk;

  InkJetPrinter(string model, string manufacturer, int availableCount, int availableInk)
      : AbstractPrinter(model, manufacturer, availableCount), availableInk(availableInk)
  {}
  virtual void print(int pages);
  virtual void show();

};


class LaserPrinter : public AbstractPrinter {

 public:
  int availableToner;

  LaserPrinter(string model, string manufacturer, int availableCount, int availableToner)
      : AbstractPrinter(model, manufacturer, availableCount), availableToner(availableToner)
  {}
  virtual void print(int pages);
  virtual void show();
	
};

void InkJetPrinter::print(int pages){
  cout << "프린트하였습니다" << endl;
  availableCount -= pages;
  availableInk -= pages;
  printedCount += pages;
}

void InkJetPrinter::show(){
  cout << "잉크젯 : " << this->model << ", " << this->manufacturer << ", 남은 종이 " << this->availableCount <<" 장, 남은 잉크 " << this->availableInk << endl;

}

void LaserPrinter::print(int pages){
  cout << "프린트하였습니다" << endl;
  availableCount -= pages;
  availableToner -= pages;
  printedCount += pages;
}

void LaserPrinter::show(){
  cout << "레이저 : " << this->model << ", " << this->manufacturer << ", 남은 종이 " << this->availableCount <<" 장, 남은 잉크 " << this->availableToner << endl;
}



int main(int argc, const char *argv[]){
  InkJetPrinter ink("Officejet V40", "HP", 5, 10);
  LaserPrinter laser("SCX-6x45", "삼성전자", 3 , 20);

  cout << "현재 작동중인 2 대의 프린터는 아래와 같다" << endl;
	
  ink.show();
  laser.show();

  int a, b;
  char answer;

  while(true){
    cout << "프린터(1:잉크젯, 2:레이저)와 매수 입력 >> " ;
    cin >> a >> b;

    if(a == 1){
      if(ink.availableCount < b){
        cout <<	"용지가 부족하여 프린트할 수 없습니다" << endl;
        continue;
      }
      else if(ink.availableInk < b){
        cout <<	"잉크가 부족하여 프린트할 수 없습니다" << endl;
        continue;
      }

      ink.print(b);
    }
    else if(a == 2){
      if(laser.availableCount < b){
        cout <<	"용지가 부족하여 프린트할 수 없습니다" << endl;
        continue;
      }
      else if(laser.availableToner < b){
        cout <<	"토너가 부족하여 프린트할 수 없습니다" << endl;
        continue;
      }

      laser.print(b);
    }
	
    ink.show();
    laser.show();


    cout << "계속 프린트하시겠습니까?(y/n)>> ";
    cin >> answer;
    if(answer == 'n')
      break;
  }
  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p455 5, AbstractGate를 상속받은 ANDGate, ORGate, XORGate를 만들고 사용해본 코드
 */
#include <iostream>
#include <string>

using namespace std;

class AbstractGate {
 protected:
  bool x,y;

 public:
  void set(bool x, bool y) { this->x = x; this-> y = y; }
  virtual bool operation() = 0;
};


class ANDGate : public AbstractGate {

 public:
  ANDGate() {}
  virtual bool operation();
};


class ORGate : public AbstractGate {

 public:
  ORGate() {}
  virtual bool operation();
};


class XORGate : public AbstractGate {

 public:
  XORGate() {}
  virtual bool operation();
};

bool ANDGate::operation(){
  if(x == true && x == y)
    return true;
  else if(x == false && x == y)
    return true;

  return false;
}

bool ORGate::operation(){
  if(x == false && x == y)
    return false;

  return true;
}

bool XORGate::operation(){
  if(x == true && x != y)
    return true;
  else if(x == false && x != y)
    return true;

  return false;
}

int main(int argc, const char *argv[]){
  ANDGate aand;
  ORGate oor;
  XORGate xxor;

  aand.set(true, false);
  oor.set(true, false);
  xxor.set(true, false);

  cout.setf(ios::boolalpha);   // 불린 값을 true, false로 출력한다

  cout << aand.operation() << endl;
  cout << oor.operation() << endl;
  cout << xxor.operation() << endl;

  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p455 3,4 LoopAdder 클래스를 상속받는 ForLoopAdder, WhileLoopAdder, DoWhileLoopAdder를 구현하고 원하는 두 숫자를 입력하면 그 사이의 합을 리턴하는 코드
 */
#include <iostream>
#include <string>

using namespace std;

class LoopAdder {
  string name;  // 루프의 이름
  int x,y,sum;
  void read();
  void write();

 protected:
  LoopAdder(string name=""){  // 루프의 이름을 받는다
    this->name = name;
  }
  int getX() {return x;}
  int getY() {return y;}

  virtual int calculate() = 0;  // 루프를 돌면서 합을 구하는 순수가상함수

 public:
  void run();
};


class ForLoopAdder : public LoopAdder {
			
 public:
  ForLoopAdder(string name) : LoopAdder(name) {}
  virtual int calculate();
};

class WhileLoopAdder : public LoopAdder{
 public:
  WhileLoopAdder(string name) : LoopAdder(name) {}
  virtual int calculate();
};


class DoWhileLoopAdder : public LoopAdder{
 public:
  DoWhileLoopAdder(string name) : LoopAdder(name) {}
  virtual int calculate();
};

void LoopAdder::read(){
  cout << name << " : " << endl;
  cout << "처음 수에서 두번째 수까지 더합니다. 두 수를 입력하세요>> ";
  cin >> this->x >> this->y;
}

void LoopAdder::write(){
  cout << this->x << "에서 " << this->y << "까지의 합 = " << sum << " 입니다" << endl;
}

void LoopAdder::run(){
  read();
  sum = calculate();
  write();
}

int ForLoopAdder::calculate(){
  int tmp = 0;
  for(int i = getX() ; i <= getY() ; i++)
    tmp += i;

  return tmp;
}

int WhileLoopAdder::calculate(){
  int tmp = 0;
  int i = getX();
  while(i <= getY()){
    tmp += i;
    i++;
  }

  return tmp;
}

int DoWhileLoopAdder::calculate(){
  int tmp = 0;
  int i = getX();

  do{
    tmp += i;
    i++;
  } while(i <= getY());
  return tmp;
}

int main(int argc, const char *argv[]){
  ForLoopAdder forLoop("For Loop");
  forLoop.run();

  WhileLoopAdder whileLoop("While Loop");
  DoWhileLoopAdder doWhileLoop("Do While Loop");

  whileLoop.run();
  doWhileLoop.run();

  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p453 1, Converter 클래스를 상속받는 WonToDollar 클래스를 생성해 원 ==> 달러로 돈을 비율에 맞춰 변환해주는 코드
 */
#include <iostream>
#include <string>

using namespace std;

class Converter {
 protected:
  double ratio;
  virtual double convert(double src) = 0;
  virtual string getSourceString() = 0;
  virtual string getDestString() = 0;

 public:
  Converter(double ratio) { this->ratio = ratio; }

  void run(){
    double src;

    cout << getSourceString() <<"을 " << getDestString() << "로 바꿉니다. " ;
    cout << getSourceString() << "을 입력하세요 >> ";
    cin >> src;
    cout << "변환 결과 : " << convert(src) << getDestString() << endl;
  }
};

class WonToDollar : public Converter{

 public:
  WonToDollar(double ratio) : Converter(ratio) {}
  virtual double convert(double src);
  virtual string getSourceString() { return "원";}
  virtual string getDestString() { return "달러";}
};

double WonToDollar::convert(double src){
  return src / ratio;
}


int main(int argc, const char *argv[]){
  WonToDollar wd(1010);
  wd.run();

  return 0;
}





------------------------------------------------------
/*
 * c++ ==> 객체지향 p557 5, exit키를 정확히 입력해야만 프로그램이 종료하는 코드  
 */
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, const char *argv[]){
  string cmd;

  cout << "cin.get(char*, int)로 문자열을 읽습니다." << endl;

  while(true){
    cout << "종료하려면 exit을 입력하세요 >> ";
    getline(cin, cmd);

    if(cmd == "exit"){
      cout << "프로그램을 종료합니다....";
      return 0;
    }
  }

  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p557 3, cin.ignore()를 사용해 hello ; 안녕 같은 구문을 입력받으면 ; 앞에 구문은 무시하고 뒤에 구문만 출력하는 예제 코드
 * 				
 * 							신기방기 :-) 무쓸모
 */
#include <iostream>

using namespace std;

int main(int argc, const char *argv[]){
  int c;

  cin.ignore(100, ';');

  while((c = cin.get()) != EOF){
    cout << (char) c;
    if(c == '\n')
      cin.ignore(100, ';');
  }

  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p557 1, cin.get() 함수를 사용해 키보드로부터 한 라인을 읽은 다음 'a'의 갯수를 세는 코드
 */
#include <iostream>

using namespace std;

int main(int argc, const char *argv[]){
  int count = 0;
  int ch;

  while((ch = cin.get()) != EOF){
    if(ch == 'a')
      count++;
    else if(ch == '\n')
      break;
  }
  cout <<  "a 문자는 총 " << count << " 개 입니다." << endl;

  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p616 9, 벡터를 사용해 텍스트 파일을 모두 읽어 원하는 라인을 입력하면 해당 줄만 보여주는 코드
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]){
  string src = "C:\\windows\\system.ini";
  string line;
  int cnt = 0;
  int num;

  vector<string> vs;

  ifstream fin(src);   // 파일 읽기

  if(!fin){
    cout << src << " 열기 오류 " << endl;
    return 0;
  }
  else
    cout << src << " 파일 읽기 완료" << endl;
	
  while(getline(fin, line)){
    vs.push_back(line);
    cnt++;
  }

  cout << "라인 번호를 입력하세요. 1보다 작은 값을 입력하면 종료" << endl;

  // num 값을 입력받아서 해당 줄의 내용을 출력한다
  while(1){
    cout << " : ";
    cin >> num;

    if(num <= 0) break;
    else if(num > cnt) continue;

    cout << vs.at(num - 1) << endl;
  }

  fin.close();

  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p615 7, 원본 파일을 바이트 단위로 거꾸로 사본에 저장하는 코드
 */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]){
  string src = "C:\\windows\\system.ini";
  string dst = "C:\\system.txt";
  string line;
  char s[1024];

  int fIndex;

  ifstream fin;   // 파일 읽기
  ofstream fout;  // 파일 쓰기

  fin.open(src, ios::binary);
  fout.open(dst);

  if(!fin){
    cout << src << " 열기 오류 " << endl;
    return 0;
  }
		
  // 파일을 읽고
  fin.read(s, 1024);
  // 실제 읽은 바이트 수를 계산하고
  int len = fin.gcount();
	
  for(int i = len ; i > 0 ; i--)
    line += s[i];

  fout << line << endl;

  fin.close();
  fout.close();

  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p615 5, c++ 소스파일에서 `//`주석문을 전부 뺀 상태로 출력하는 코드
 */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]){
  string src = "C:\\Users\\vdl\\Downloads\\test.cpp";
  string dst = "C:\\Users\\vdl\\Downloads\\test2.cpp";
  string line;

  int fIndex;

  ifstream fin(src);   // 파일 읽기
  ofstream fout(dst);  // 파일 쓰기

  if(!fin){
    cout << src << " 열기 오류 " << endl;
    return 0;
  }

  while(getline(fin, line)){
    fIndex = line.find("//", 0);
		
    if(fIndex != -1)
      line.replace(fIndex, 2 , "");

    cout << line << endl;
    fout << line << endl;
  }
  cout << "Done Save! at : " << dst << endl;
  fin.close();
  fout.close();

  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p614 3, 영문텍스트 파일을 읽고 대문자로 출력하는 코드
 */
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

int main(int argc, const char *argv[]){
  char* file = "c:\\windows\\system.ini";

  ifstream fin(file);
  if(!fin){
    cout << file << " 열기 오류 " << endl;
    return 0;
  }

  int count = 0;
  char c;

  while((c = fin.get()) != EOF){
    cout << char(toupper(c));
    count++;
  }

  cout << "읽은 바이트 수는 " << count << endl;
  fin.close();

  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p614 2, c:\windows\system.ini 파일을 읽고 라인번호를 붙여 화면에 출력하는 코드
 */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]){
  char* file = "c:\\windows\\system.ini";
  string line;

  ifstream fin(file);
  if(!fin){
    cout << file << " 열기 오류 " << endl;
    return 0;
  }

  int count = 0;
  int lineNum = 1;

  // 이런식으로 getline을 while하고 같이 쓸 수 있구만 :-)
  while(getline(fin, line)){
    cout << lineNum++ << " : " << line << endl;
  }


  cout << "읽은 바이트 수는 " << count << endl;
  fin.close();

  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 예제 12-3, get()을 이용해 텍스트 파일 읽기
 */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]){
  char* file = "c:\\windows\\system.ini";

  ifstream fin(file);
  if(!fin){
    cout << file << " 열기 오류 " << endl;
    return 0;
  }

  int count = 0;
  int c;
  while((c=fin.get()) != EOF){
    cout << (char)c;
    count++;
  }

  cout << "읽은 바이트 수는 " << count << endl;
  fin.close();

  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 예제 12-1, 키보드로 입력받아 텍스트 파일 저장하기
 */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]){
	
  char name[10], dept[20];
  int sid;

  cout << "이름>> ";
  cin >> name;
  cout << "학번>> ";
  cin >> sid;
  cout << "학과>> ";
  cin >> dept;

  ofstream fout("c:\\student.txt");
  if(!fout){
    cout << "student.txt 파일을 열 수 없다";
  }

  fout << name << endl;
  fout << sid << endl;
  fout << dept << endl;

  fout.close();

  return 0;
}





------------------------------------------------------
/*
 * c++ ==> 객체지향 p410 5,6 , BaseArray 클래스를 상속받는 MyQueue 클래스와 MyStack 클래스를 작성하고 사용해 본 코드
 */
#include <iostream>
#include <string>

using namespace std;

class BaseArray {
 private:
  int capacity;
  int *mem;

 protected:
  BaseArray(int capacity=100){
    this->capacity = capacity;
    mem = new int[capacity];
  }
  ~BaseArray() { delete[] mem; }

  void put(int index, int val) { mem[index] = val; }
  int get(int index) { return mem[index]; }
  int getCapacity() { return capacity; }
};

class MyQueue : public BaseArray {
  int count;
 public:
  MyQueue(int cap) : BaseArray(cap) {
    count = 0;
  }

  int capacity();
  void enqueue(int val);
  int dequeue();
  int length();
};

int MyQueue::capacity(){
  return getCapacity();
}

void MyQueue::enqueue(int val){
  put(count++, val);
}

int MyQueue::dequeue(){
  return get(--count);
}

int MyQueue::length(){
  return count;
}

class MyStack : public BaseArray {

 public:
		
};

int main(int argc, const char *argv[]){
  MyQueue mQ(100);

  int n;
  cout << "큐에 삽입할 5개의 정수를 입력하라>> ";

  for(int i =0 ; i< 5; i++){
    cin >> n;
    mQ.enqueue(n);
  }

  cout << "큐의 용량: " << mQ.capacity() << ", 큐의 크기: " << mQ.length() << endl;

  cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";

  while(mQ.length() != 0){
    cout << mQ.dequeue() << ' ';
  }

  cout << endl << "큐의 현재 크기 : " << mQ.length() << endl;

  return 0;
}






------------------------------------------------------
/*
 * c++ ==> 객체지향 p409 3,4 , Point 클래스를 상속한 ColorPoint 클래스를 정의하고 사용해본 코드
 */
#include <iostream>
#include <string>

using namespace std;

class Point {
  int x,y;
 public:
  Point(int x, int y) { this->x = x; this->y = y;}

  int getX() { return x; }
  int getY() { return y; }

 protected:
  void move(int x, int y) { this->x = x; this->y = y; }
};

class ColorPoint : public Point {
  string color;

 public:
  ColorPoint()
      : Point(0,0), color("BLACK")
  {}
	
  ColorPoint(int x, int y, string color = "RED")
      : Point(x,y), color(color)
  {}

  void setPoint(int x, int y);
  void setColor(string color);
  void show();
};

void ColorPoint::setPoint(int x, int y){
  move(x,y);
}
void ColorPoint::setColor(string color){
  this->color = color;
}
void ColorPoint::show(){
  cout << color << "색으로 (" << getX() << ", " << getY() <<") 위치한 점입니다" << endl;
}

int main(int argc, const char *argv[]){
  ColorPoint zeroPoint;
  ColorPoint cp(5, 5, "RED");
  ColorPoint cp2(5, 5);

  zeroPoint.show();

  cp.setPoint(10, 20);
  cp.setColor("BLUE");
  cp.show();

  cp2.setPoint(10, 20);
  cp2.setColor("BLUE");
  cp2.show();

  return 0;
}





------------------------------------------------------
/*
 * c++ ==> 객체지향 p408 1,2, Circle 클래스를 상속받은 NamedCircle 클래스를 작성하고 사용해본 코드 (미완성)
 */
#include <iostream>
#include <string>

using namespace std;

class Circle {
  int radius;

 public:
  Circle(int radius=0) { this->radius = radius;}

  int getRadius() { return radius;}
  void setRadius(int radius) { this->radius = radius;}
  double getArea() { return 3.14 * radius * radius;}
};


class NamedCircle : public Circle{
  string name;
  string *nameArray;

 public:
  NamedCircle();
  NamedCircle(int radius, string name) : Circle(radius), name(name) {}
  ~NamedCircle();

  void show();
  void getDataArray();
};

NamedCircle::NamedCircle(){
	
}	

void NamedCircle::getDataArray(){

}

NamedCircle::~NamedCircle(){
  delete[] nameArray;
}

void::show(){
  cout << "반지름이 " << getRadius() << "인 " << this->name << endl;
}


int main(int argc, const char *argv[]){
  NamedCircle waffle(3, "waffle");
  NamedCircle pizza[5];

  waffle.show();
  return 0;
}




------------------------------------------------------


기말고사
기말고사
기말고사
기말고사
중간고사
중간고사
중간고사
중간고사


------------------------------------------------------
/*
 * c++ ==> 객체지향 p361 10, Stack 클래스르 만들고 Push를 << 연산자를, Pop으로 >> 연산자를 오버로딩한 코드
 */
#include <iostream>
#include <string>
using namespace std;

static int count = 0;

class Stack{
  int *data;

 public:
  Stack();
  ~Stack();
  Stack& operator<<(int x);
  void operator>>(int& x);
  bool operator!();
};

Stack::Stack(){
  data = new int[3];
}

Stack::~Stack(){
  delete[] data;
}

Stack& Stack::operator<<(int x){
  this->data[count] = x;
  count++;
  return *this;
}

void Stack::operator>>(int& x){
  x = this->data[count - 1];
  count--;
}

bool Stack::operator!(){
  if(count == 0) return true;
  return false;
}

int main(int argc, char *argv[]){
  Stack stack;
  stack << 3 << 5 << 10;

  while(true){
    if(!stack) break;
    int x;
    stack >> x;
    cout << x << ' ';
  }

  cout << endl;
  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p360 9, 통계를 내는 Statistics 클래스를 생성하고 << 연산자를 통해 객체에 값을 받고 >> 값으로 평균을 리턴하며 !를 통해 객체의 값이 있는지 없는지 검사하고 ~를 통해 전체 데이터의 갯수를 출력하는 코드
 */
#include <iostream>
#include <string>
using namespace std;

static int count = 0;

class Statistics{
  int *num;

 public:
  Statistics();
  ~Statistics();
  bool operator!();
  Statistics& operator<<(int x);
  void operator>>(int& x);
  void operator~();
};

Statistics::Statistics(){
  num = new int[7];
}

Statistics::~Statistics(){
  delete[] num;
}

// ! 연산자 오버로딩
bool Statistics::operator!(){
  if(count == 0)
    return false;

  return true;
}

// << 연산자 오버로딩
Statistics& Statistics::operator<<(int x){
  this->num[count] = x;
  count++;
  return *this;
}

// 평균을 전달하는 >> 연산자 오버로딩
void Statistics::operator>>(int& x){
  int avg = 0;

  for(int i = 0 ; i < count ; i++){
    avg += this->num[i];
  }
  avg /= count;
  x = avg;
}

// 데이터를 출력하는 ~ 연산자 오버로딩
void Statistics::operator~(){
  for(int i = 0 ; i < count ; i++){
    cout << this->num[i] << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]){
  Statistics stat;

  if(!stat) cout << "현재 통계 데이타가 없습니다." << endl;

  int x[5];
  cout << "5 개의 정수를 입력하라>> ";
  for (int i=0; i<5 ; i++) cin >> x[i];

  for(int i = 0; i<5 ; i++) stat << x[i]; // x[i] 값을 통계객체에 삽입한다

  stat << 100 << 200; // 100, 200을 통계 객체에 삽입한다
  ~stat; // 통계 데이타를 모두 출력한다

  int avg;
  stat >> avg;   // 통계 객체로부터 평균을 받는다
  cout << "avg=" << avg << endl; // 평균을 출력한다

  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p359 7,8, Circle 클래스를 생성하여 전위연산자와 후위연산자, b = 1 + a 같은 연산자를 외부함수로 구현해본 코드
 */
#include <iostream>
#include <string>
using namespace std;

class Circle{
  int radius;

 public:
  Circle() :radius(0) {}
  Circle(int radius) : radius(radius) {}
  void show();
  // friend 외부함수 등록
  friend Circle operator++(Circle& c);
  friend Circle operator++(Circle& c, int a);
  friend Circle operator+(int a, Circle& c);
};

void Circle::show(){
  cout << "radius = " << this->radius <<" 인 원" << endl;
}

// 전위연산자 ++a 구현
Circle operator++(Circle& c){
  c.radius++;
  return c;
}

// 후위연산자 a++ 구현
Circle operator++(Circle& c, int a){
  Circle tmp = c;
  c.radius++;
  return tmp;
}

// d = 1 + c 연산자 구현
Circle operator+(int a, Circle& c){
  Circle tmp;
  tmp.radius += 1 + c.radius;

  return tmp;
}

int main(int argc, char *argv[]){
  Circle a(5);
  Circle b(4);
  Circle c(5);
  Circle d(4);

  ++a;
  b = a++;

  a.show();
  b.show();

  d = 1 + c;
  c.show();
  d.show();

  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p358 5,6, 2차원 행렬을 추상화한 Matrix 클래스를 생성해서 행렬값을 입력받고 + , +=, ==, <<, >> 연산자를 오버로딩해 본 코드
 */
#include <iostream>
#include <string>
using namespace std;

class Matrix {
  int mat[4];

 public:
  Matrix(int a, int b, int c, int d);
  void show();
  Matrix operator+(Matrix a);
  Matrix operator+=(Matrix a);
  bool operator==(Matrix m);
  void operator>>(int x[]);
  void operator<<(int x[]);
};

// 생성자
Matrix::Matrix(int a = 0, int b = 0, int c = 0, int d=0) {
  mat[0] = a;
  mat[1] = b;
  mat[2] = c;
  mat[3] = d;
}

// 행렬을 출력하는 함수
void Matrix::show() {
  cout << "{ " << mat[0] << " " << mat[1] << " " << mat[2] << " " << mat[3] << " }" << endl;
}

// == 연산자 오버로딩
bool Matrix::operator==(Matrix m) {
  if (mat[0] == m.mat[0])
    if (mat[1] == m.mat[1])
      if (mat[2] == m.mat[2])
        if (mat[3] == m.mat[3])
          return true;
  return false;
}

// + 연산자 오버로딩
Matrix Matrix::operator+(Matrix a) {
  Matrix tmp(a.mat[0] + this->mat[0], a.mat[1] + this->mat[1], a.mat[2] + this->mat[2], a.mat[3] + this->mat[3]);
  return tmp;
}

// += 연산자 오버로딩
Matrix Matrix::operator+=(Matrix a) {
  this->mat[0] += a.mat[0];
  this->mat[1] += a.mat[1];
  this->mat[2] += a.mat[2];
  this->mat[3] += a.mat[3];
  return *this;
}

// >> 연산자 오버로딩
void Matrix::operator>>(int x[]){
  x[0] = this->mat[0];
  x[1] = this->mat[1];
  x[2] = this->mat[2];
  x[3] = this->mat[3];

}

// << 연산자 오버로딩
void Matrix::operator<<(int x[]){
  this->mat[0] = x[0];
  this->mat[1] = x[1];
  this->mat[2] = x[2];
  this->mat[3] = x[3];

}

int main(int argc, const char *argv[]) {
  Matrix a(1, 2, 3, 4);
  Matrix b(2, 3, 4, 5);
  Matrix c;
  Matrix d(4,3,2,1);
  Matrix e;
  int x[4];
  int y[4] = {1,2,3,4};

  c = a + b;
  a += b;

  a.show();
  b.show();
  c.show();

  if (a == c)
    cout << "a and c are the same" << endl;

  d >> x;  // d의 각 원소를 배열 x에 복사
  e << y;  // 배열 y의 원소 값을 e의 각 원소에 설정

  for(int i = 0 ; i < 4; i++) cout << x[i] << ' '; // x[] 출력
  cout << endl;

  e.show();

  return 0;
}




------------------------------------------------------
/*
  c++ ==> 객체지향 p357 1,2,3,4, 책의 이름과 가격, 페이지수를 입력받는 Book 클래스를 생성하고 -= += ! < == 의 연산자 오버로딩을 수행하는 코드
*/
#include <iostream>
#include <string>
using namespace std;

class Book {
  string title;
  int price, pages;

 public:
  Book(string title = "", int price = 0, int pages = 0) {
    this->title = title, this->price = price, this->pages = pages;
  }
  void show() {
    cout << title << ' ' << price << "원 " << pages << " 페이지" << endl;
  }
  string getTitle() { return this->title; }
  Book operator+=(int a);
  Book operator-=(int a);
  bool operator==(int a);
  bool operator==(string str);
  bool operator==(Book b);
  bool operator!();
  bool operator<(Book b);
};

// += 연산자 오버로딩
Book Book::operator+=(int a) {
  this->price += a;
  return *this;
}

// -= 연산자 오버로딩
Book Book::operator-=(int a) {
  this->price -= a;
  return *this;
}

// == 연산자 오버로딩
bool Book::operator==(int a) {
  if (this->price == a)
    return true;
  return false;
}

// == 연산자 오버로딩
bool Book::operator==(string str) {
  if (this->title == str)
    return true;
  return false;
}

// == 연산자 오버로딩
bool Book::operator==(Book b) {
  if (this->title == b.title)
    if (this->price == b.price)
      if (this->pages == b.pages)
        return true;
  return false;
}

// ! 연산자 오버로딩
bool Book::operator!() {
  if (this->price == 0)
    return true;
  return false;
}

// < 연산자 오버로딩
bool Book::operator<(Book b) {
  if (this->title < b.title)
    return true;
  return false;
}

int main(int argc, const char *argv[]) {
  Book a("청춘", 20000, 300);
  Book b("미래", 30000, 500);
  Book c("명품 c++", 30000, 500);
  Book d("고품 c++", 30000, 500);
  Book book("벼룩시장", 0, 50);
  string bookName;

  // += -= 연산자 오버로딩
  a += 500;
  b -= 500;
  a.show();
  b.show();

  // == 연산자 오버로딩 3가지 케이스
  if (c == 30000) cout << "정가 30000원" << endl;
  if (c == "명품 c++") cout << "명품 c++ 입니다" << endl;
  if (c == d) cout << "두 책이 같은 책입니다" << endl;


  // ! 연산자 오버로딩
  if (!book) cout << "공짜다" << endl;


  // < 연산자 오버로딩
  cout << "책 이름을 입력하세요>> ";
  getline(cin, bookName);
  if (b < a)
    cout << a.getTitle() << "이 " << bookName << "보다 뒤에 있구나!" << endl;

  return 0;
}



------------------------------------------------------
/*
  c++ ==> 객체지향 p350 open challange, 히스토그램 클래스에 <<, ! 연산자를 오버로딩해서 << 문으로 문장을 추가하고 ! 문으로 알파벳의 갯수만큼 히스토그램을 만드는 코드
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;

class Histogram{
  string sentence;

 public:
  Histogram(string str) : sentence(str) {}
	
  Histogram& operator<< (string str);
  Histogram& operator<< (char c);
  void operator! ();
};

// << 연산자 오버로딩 : string 버전
Histogram& Histogram::operator<< (string str){
  this->sentence += str;
  return *this;
}

// << 연산자 오버로딩 : char 버전
Histogram& Histogram::operator<< (char c){
  this->sentence += c;
  return *this;
}

// ! 연산자로 히스토그램을 출력한다
void Histogram::operator!(){
  int len = 0;
  int spaceLen = 0;
  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
  char star = '*';

  cout << this->sentence << endl;

  // 대문자를 소문자로 바꿔주는 구문!
  transform(this->sentence.begin(), this->sentence.end(), this->sentence.begin(), ::tolower);

  len = this->sentence.length();

  // regex 정규표현식을 사용해서 특수문자의 갯수만큼 빼준다
  regex rx("[^a-zA-z]");

  // 알파벳을 제외한 나머지 특수문자의 개수를 세는 코드!
  int match_count(distance(sregex_iterator(this->sentence.begin(), this->sentence.end(), rx), sregex_iterator()));

  len -= match_count;

  cout << "총 알파벳 개수 : " << len << endl;

  // count 함수를 사용해 알파벳의 갯수를 리턴한다
  a = count(sentence.begin(), sentence.end(), 'a');
  b = count(sentence.begin(), sentence.end(), 'b');
  c = count(sentence.begin(), sentence.end(), 'c');
  d = count(sentence.begin(), sentence.end(), 'd');
  e = count(sentence.begin(), sentence.end(), 'e');
  f = count(sentence.begin(), sentence.end(), 'f');
  g = count(sentence.begin(), sentence.end(), 'g');
  h = count(sentence.begin(), sentence.end(), 'h');
  i = count(sentence.begin(), sentence.end(), 'i');
  j = count(sentence.begin(), sentence.end(), 'j');
  k = count(sentence.begin(), sentence.end(), 'k');
  l = count(sentence.begin(), sentence.end(), 'l');
  m = count(sentence.begin(), sentence.end(), 'm');
  n = count(sentence.begin(), sentence.end(), 'n');
  o = count(sentence.begin(), sentence.end(), 'o');
  p = count(sentence.begin(), sentence.end(), 'p');
  q = count(sentence.begin(), sentence.end(), 'q');
  r = count(sentence.begin(), sentence.end(), 'r');
  s = count(sentence.begin(), sentence.end(), 's');
  t = count(sentence.begin(), sentence.end(), 't');
  u = count(sentence.begin(), sentence.end(), 'u');
  v = count(sentence.begin(), sentence.end(), 'v');
  w = count(sentence.begin(), sentence.end(), 'w');
  x = count(sentence.begin(), sentence.end(), 'x');
  y = count(sentence.begin(), sentence.end(), 'y');
  z = count(sentence.begin(), sentence.end(), 'z');

  cout << "a(" << a <<") " << string(a,star) << endl;
  cout << "b(" << b <<") " << string(b,star) << endl;
  cout << "c(" << c <<") " << string(c,star) << endl;
  cout << "d(" << d <<") " << string(d,star) << endl;
  cout << "e(" << e <<") " << string(e,star) << endl;
  cout << "f(" << f <<") " << string(f,star) << endl;
  cout << "g(" << g <<") " << string(g,star) << endl;
  cout << "h(" << h <<") " << string(h,star) << endl;
  cout << "i(" << i <<") " << string(i,star) << endl;
  cout << "j(" << j <<") " << string(j,star) << endl;
  cout << "k(" << k <<") " << string(k,star) << endl;
  cout << "l(" << l <<") " << string(l,star) << endl;
  cout << "m(" << m <<") " << string(m,star) << endl;
  cout << "n(" << n <<") " << string(n,star) << endl;
  cout << "o(" << o <<") " << string(o,star) << endl;
  cout << "p(" << p <<") " << string(p,star) << endl;
  cout << "q(" << q <<") " << string(q,star) << endl;
  cout << "r(" << r <<") " << string(r,star) << endl;
  cout << "s(" << s <<") " << string(s,star) << endl;
  cout << "t(" << t <<") " << string(t,star) << endl;
  cout << "u(" << u <<") " << string(u,star) << endl;
  cout << "v(" << v <<") " << string(v,star) << endl;
  cout << "w(" << w <<") " << string(w,star) << endl;
  cout << "x(" << x <<") " << string(x,star) << endl;
  cout << "y(" << y <<") " << string(y,star) << endl;
  cout << "z(" << z <<") " << string(z,star) << endl;
}

int main(int argc, char *argv[]){
  Histogram song("Wise men say, \nonly fools rush in But I can't help, \n");
  song << "falling" << " in love with you." << "- by ";
  song << 'k' << 'i' << 't';
  !song; // histogram 그리기

  return 0;
}


------------------------------------------------------
/*
  c++ ==> 객체지향 p309 8, 디버깅에 필요한 Trace 클래스를 만들어 f() 함수가 동작하는 동안 Trace 정보를 저장해서 필요할 때 출력하는 코드
*/
#include <iostream>
#include <string>
using namespace std;

// 우선 100개의 트레이스 정보만 저장한다. 프로그램 확장시 동적으로 받도록 변경한다
static string trace[100] = string();
static int count =0;

class Trace{

 public:
  Trace() {}
  static void put(string func, string sentence);
  static void print(string func);
};

// Trace 객체에 데이터를 입력하는 함수
void Trace::put(string func, string sentence){
  trace[count] += func + ": " + sentence;
  count++;
}

// Trace 정보를 출력하는 함수. 앞에 함수의 이름을 인식해서 원하는 함수 정보만 출력한다
void Trace::print(string func = string()){
  if(func == string()){
    cout << "------ 모든 Trace 정보를 출력합니다 -------" << endl;

    for (int i =0 ; i < count ; i++)
      cout << trace[i] << endl;
    return;
  }

  int len = func.length();
  int isThere = 0;

  cout << "------ " << func << "태그의 정보를 출력합니다 -------" << endl;
  for(int i = 0 ; i < count ; i++){
    // 함수의 이름이 있다면 있는 것만 출력한다
    isThere = trace[i].find(func, 0);
    if(isThere != -1)
      cout << trace[i] << endl;
  }
}

void f(){
  int a,b,c;
  cout << "두 개의 정수를 입력하세요>> ";
  cin >> a >> b;

  Trace::put("f()", "정수를 입력 받았음");  // 디버깅 정보 저장
  c = a + b;
  Trace::put("f()", "합 계산"); // 디버깅 정보 저장
  cout << "합은 " << c << endl;
}


int main(int argc, char *argv[]){
  Trace::put("main()", "프로그램 시작합니다");
  f();
  Trace::put("main()" , "종료");

  Trace::print("f()");  // f() 태그를 가진 디버깅 정보를 모두 출력한다
  Trace::print();  // 모든 디버깅 정보를 출력한다
  return 0;
}



------------------------------------------------------
/*
  c++ ==> 객체지향 p307 5, 동일한 크기로 배열을 int -> double, double -> int로 변환하는 static 함수 2개를 ArrayUtility에 추가시키고 이를 사용한 코드
*/
#include <iostream>
#include <string>
using namespace std;

class ArrayUtility{

 public:
  // 2개의 static 멤버함수 추가
  static void intToDouble(int source[], double dest[], int size);
  static void doubleToInt(double source[], int dest[], int size);
};

void ArrayUtility::intToDouble(int source[], double dest[], int size){
  for(int i = 0; i < size ; i++)
    dest[i] = source[i];
}

void ArrayUtility::doubleToInt(double source[], int dest[], int size){
  for(int i = 0; i < size ; i++)
    dest[i] = source[i];
}


int main(int argc, char *argv[]){
  int x[] = {1,2,3,4,5};
  double y[5];
  double z[] = {9.9, 8.8 , 7.7, 6.6, 5.6};

  ArrayUtility::intToDouble(x, y, 5); // x[] -> y[]
  for(int i = 0; i< 5; i++) cout << y[i] << ' ';
  cout << endl;

  ArrayUtility::doubleToInt(z, x, 5); // z[] -> x[]
  for(int i = 0; i< 5; i++) cout << x[i] << ' ';
  cout << endl;

  return 0;
}


------------------------------------------------------
/*
  c++ ==> 객체지향 p305 1, add 함수를 default parameter를 통해 만들어 배열을 입력받아 합을 출력하는 코드
*/
#include <iostream>
#include <string>

using namespace std;

int nullArray[] = {0,0,0,0,0};

// 배열의 default parameter는 다음과 같이 해야 한다
int add(int a[], int num, int b[] = nullArray){
  int sum = 0;

  for(int i = 0 ; i < num ; i++)
    sum += a[i];

  for(int i = 0 ; i < num ; i++)
    sum += b[i];

  return sum;
}

int main(int argc, char *argv[]){
  int a[] = {1,2,3,4,5};
  int b[] = {6,7,8,9,10};

  int c = add(a, 5);
  int d = add(a, 5, b);

  cout << c << endl;
  cout << d << endl;

  return 0;
}



------------------------------------------------------
/*
  c++ ==> 객체지향 p301 open challange, up & down 게임을 만들어 2명이서 up & down 게임을 해보는 코드
*/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;
// 정답을 저장하는 static int 변수를 선언한다
static int answer;

// 2명의 Player를 선언하기 위한 클래스
class Person {
  string name;

 public:
  Person() {}
  void setName(string name){
    this->name = name;
  }
  string getName() {
    return this->name;
  }
};

// UpAndDownGame을 실제로 수행하는 클래스
class UpAndDownGame{
  Person *p;

 public:
  UpAndDownGame();
  ~UpAndDownGame();
  void setPlayer(string name1, string name2);
  void startGame();
};

// 생성자
UpAndDownGame::UpAndDownGame(){
  int n = rand() % 100;
  p = new Person[2];
  answer = n;
}

// 소멸자
UpAndDownGame::~UpAndDownGame(){
  delete[] p;
}

// 플레이어의 이름을 세팅하는 함수
void UpAndDownGame::setPlayer(string name1, string name2){
  p[0].setName(name1);
  p[1].setName(name2);
}

// 게임을 시작하는 함수
void UpAndDownGame::startGame(){
  int top=99;
  int bottom=0;
  int num;
  int i = 0;

  while(1){
    cout << "답은 " << bottom << "과 " << top << " 사이에 있습니다" << endl;
    cout << p[i].getName() << ">> ";
    cin >> num;

    if(answer > num)
      bottom = num;
    else if(answer < num)
      top = num;

    if(num == answer){
      cout << p[i].getName() <<"이(가) 이겼습니다!" << endl;
      break;
    }
    i++;
    if(i > 1) i = 0;
  }
}


int main(int argc, const char *argv[]){
  // 난수를 생성하기 위해 srand()함수를 사용한다
  srand((unsigned)time(0));
  UpAndDownGame udgame;

  cout << "Up & Down 게임을 시작합니다" << endl;
  udgame.setPlayer("류현진", "손연재");
  udgame.startGame();
  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p268 8, Book 클래스에서 깊은 복사를 사용해 복사를 해본 코드
 */
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Book{
  char *title;
  int price;

 public:
  Book(char* title, int price);
  Book(Book& b);
  ~Book();
  void set(char* title, int price);
  void show() { cout << title << ' ' << price << "원" << endl; }
};

Book::Book(char* title, int price) : price(price){
  this->title = new char[strlen(title) +1];
  strcpy(this->title, title);
}

Book::Book(Book& b) : price(b.price){ 
  this->title = new char[strlen(b.title) + 1];
  strcpy(this->title, b.title);
  this->title = "명품자바";
}

Book::~Book(){
  cout << this->title << " deleted!" << endl;
  delete[] title;
}

void Book::set(char* title, int price){
  this->title = new char[strlen(title) +1];
  strcpy(this->title, title);
  this->price = price;
}


int main(int argc, const char *argv[]){
  Book cpp("명품C++", 10000);
  Book java = cpp;

  cpp.show();
  java.show();
	
  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p267 7, add를 통해 값을 누적하는 Accumulator 클래스를 생성ㅎ고 .add(5).add(6).add(7)을 통해 값을 계속 누적시킨후 출력하는 코드
 */
#include <iostream>
#include <string>
using namespace std;

class Accumulator {
  int value;

 public:
  Accumulator(int value);
  Accumulator(Accumulator& a);
  Accumulator& add(int n);  // 값을 계속 누적하기 위해 참조리턴을 하는 함수
  int get();
};

Accumulator::Accumulator(int value) : value(value)
{}

Accumulator::Accumulator(Accumulator& a) {
  this->value = a.value;
}

// add 함수를 통해 value 값을 계속해서 누적하기 위해 *this를 반환하는 함수
Accumulator& Accumulator::add(int n) {
  this->value += n;
  return *this;
}

int Accumulator::get() {
  return this->value;
}

int main(int argc, const char *argv[]) {
  Accumulator acc(10);

  acc.add(5).add(6).add(7);
  cout << acc.get() << endl;

  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p265 6, p265 5번문제에 스택에 저장할 수 있는 크기를 동적할당하게 작성하고 복사생성자 또한 구현해본 코드
 */
#include <iostream>
#include <string>
using namespace std;

class MyIntStack {
  int *p;
  int size;
  int tos; // stack의 꼭대기를 가르키는 인덱스

 public:
  MyIntStack();
  MyIntStack(int size);
  MyIntStack(MyIntStack& s); // 복사생성자 구현
  ~MyIntStack();

  bool push(int n);
  bool pop(int &n);
};

MyIntStack::MyIntStack() :tos(0) {
  p = new int[10];
}

MyIntStack::MyIntStack(int size) : size(size), tos(0) {
  p = new int[size];
}

// 복사생성자를 사용해본 코드 
MyIntStack::MyIntStack(MyIntStack& s) {
  this->size = s.size;
  this->tos = s.tos;

  // 배열에 대한 복사가 이뤄져야하므로 아래와 같이 복사한다
  this->p = new int[size];
  for(int i = 0 ; i < s.size ; i++)
    this->p[i] = s.p[i];
}

MyIntStack::~MyIntStack() {
  delete[] this->p;
}

bool MyIntStack::push(int n) {
  if (tos < size) {
    p[tos] = n;
    tos++;
    return true;
  }
  return false;
}

bool MyIntStack::pop(int &n) {
  if (tos >= 0) {
    n = p[tos - 1];
    tos--;
    return true;
  }
  return false;
}

int main(int argc, const char *argv[]) {
  MyIntStack a(10);
  a.push(10);
  a.push(20);

  MyIntStack b = a;
  b.push(30);

  int n;
  a.pop(n);
  cout << "스택 a에서 팝한 값 " << n << endl;
  b.pop(n);
  cout << "스택 b에서 팝한 값 " << n << endl;

  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p265 5, 정수를 저장하는 MyIntStack 클래스를 작성하고 10개의 배열만 push, pop을 통해 입력출하는 코드
 */
#include <iostream>
#include <string>

class MyIntStack{
  int p[10]; // 최대 10개의 정수 저장
  int tos; // stack의 꼭대기를 가르키는 인덱스

 public:
  MyIntStack();
  bool push(int n);
  bool pop(int &n);
};

MyIntStack::MyIntStack() : tos(0) {
  p[10] = {0,};
}

bool MyIntStack::push(int n){
  if(tos < 10){
    p[tos] = n;
    tos++;
    return true;
  }
  return false;
}

bool MyIntStack::pop(int &n){
  if(tos >= 0){
    n = p[tos];
    tos--;
    return true;
  }
  return false;
}

int main(int argc, const char *argv[]){
  MyIntStack a;

  for (int i = 0; i < 11; i++) {
    if(a.push(i))  cout << i << ' ';
    else cout<< endl << i + 1 << " 번째 stack full" << endl;
  }
  int n;

  for (int i = 0; i < 11 ; i++) {
    if(a.pop(n)) cout << n << ' ';
    else cout << endl << i + 1 << " 번째 stack empty";
  }
  cout << endl;
	
  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p265 4, 참조자를 리턴하는 find() 함수를 작성하고 Mike에서 M 문자를 찾은 다음 m으로 수정하는 코드
 */
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// a 문자열에서 c를 찾아 참조자를 리턴하는 함수
char& find(char a[], char c, bool& success) {
  int len = strlen(a);
	
  for (int i = 0; i < len; i++) {
    if (a[i] == c) {
      success = true;
      return a[i];
    }
  }
  success = false;
}

int main(int argc, const char *argv[]) {
  char s[] = "Mike";
  bool b = false;
  char& loc = find(s, 'M', b);

  if (b == false) {
    cout << "M을 발견할 수 없다" << endl;
    return 0;
  }

  loc = 'm';
  cout << s << endl;
  return 0;
}




------------------------------------------------------
/*
 *	c++ ==> 객체지향 p259 open challange, 영문텍스트와 모스부호 변환기를 만들어본 코드. 영문자 + 특수문자 <==> 모스부호가 상호변환 가능하다
 */
#include <iostream>
#include <string>
using namespace std;

// 알파벳과 숫자를 상수로 선언한다
const string ALPHA = "abcdefghijklmnopqrstuvwxyz";
const char DIGIT[10] = {'0','1','2','3','4','5','6','7','8','9'};

// 문자 하나를 입력받아 그 문자가 어느 위치에 있는지 알려주는 함수 
int getpos(char c) {
  int pos;
  const char * alphabet = "abcdefghijklmnopqrstuvwxyz0123456789/?,.+=";
  const char * found;

  c = tolower((unsigned char)c);
  found = strchr(alphabet, c);
  pos = found - alphabet;
  if (!found)
    pos = 0;
  else if (pos == 42)
    pos = 0;
  else
    pos++;
  return pos - 1;
}

// 모스부호 <==> 영문자특수문자 변환을 해주는 클래스
class Morse {
  string alphabet[26];
  string digit[10];
  string slash, question, comma, period, plus, equal;

 public:
  Morse();
  void text2Morse(string text, string& morse);
  void morse2Text(string morse, string& text);
};

// 각각의 모스부호를 입력한다
Morse::Morse() {
  alphabet[0] = ".-";   //a
  alphabet[1] = "-..."; //b
  alphabet[2] = "-.-."; //c
  alphabet[3] = "-..";  //d
  alphabet[4] = ".";    //e
  alphabet[5] = "..-."; //f
  alphabet[6] = "--."; //g
  alphabet[7] = "....";//h
  alphabet[8] = "..";//i
  alphabet[9] = ".---";//j
  alphabet[10] = "-.-";//k
  alphabet[11] = ".-..";//l
  alphabet[12] = "--";//m
  alphabet[13] = "-.";//n
  alphabet[14] = "---";//o
  alphabet[15] = ".--.";//p
  alphabet[16] = "--.-";//q
  alphabet[17] = ".-.";//r
  alphabet[18] = "...";//s
  alphabet[19] = "-";//t
  alphabet[20] = "..-";//u
  alphabet[21] = "...-";//v
  alphabet[22] = ".--";//w
  alphabet[23] = "-..-";//x
  alphabet[24] = "-.--";//y
  alphabet[25] = "--..";//z

  digit[0] = "-----";
  digit[1] = ".----";
  digit[2] = "..---";
  digit[3] = "...--";
  digit[4] = "....-";
  digit[5] = ".....";
  digit[6] = "-....";
  digit[7] = "--...";
  digit[8] = "----..";
  digit[9] = "----.";

  slash = "-..-.";
  question = "..--..";
  comma = "--..--";
  period = ".-.-.-";
  plus = ".-.-.";
  equal = "-...-";
}

// 텍스트를 입력받으면 모스부호를 반환하는 멤버함수
void Morse::text2Morse(string text, string& morse) {
  int i = 0;
  int j = 0;
  int len = text.length();

  while (1) {
    j = getpos(text[i]);

    if (text[i] == ' ')
      morse += "  ";

    if (j >= 0 && j < 26)
      morse += this->alphabet[j] + ' ';
    else if (j >= 26 && j < 36)
      morse += this->digit[j - 26] + ' ';
    else if (j == 36)
      morse += this->slash + ' ';
    else if (j == 37)
      morse += this->question + ' ';
    else if (j == 38)
      morse += this->comma + ' ';
    else if (j == 39)
      morse += this->period + ' ';
    else if (j == 40)
      morse += this->plus + ' ';
    else if (j == 41)
      morse += this->equal + ' ';

    i++;
    if (i == len) break;
  }
}

// 모스부호를 입력받으면 텍스트를 반환하는 멤버함수
void Morse::morse2Text(string morse, string& text) {
  int first = 0;
  int last = 0;
  int i = 0;
  int space = 0;
  int lenMorse = morse.length();
  string tmp;

  while (1) {
    // ' ' 스페이스가 모스부호 한 단어를 구분하므로 find로 인덱스값을 찾는다
    last = morse.find(' ', first);
		
    // 문장의 끝에 도달하면 루프탈출
    if (last == -1)
      break;

    // 한 단어를 tmp에만 뽑아서 저장한다
    tmp = morse.substr(first, last - first);
		
    // 무한루프 2개를 돌면서 알파벳과 숫자를 발견하면 text에 더해준다
    while (1) {
      if (tmp == this->alphabet[i])
        text += ALPHA[i];
      i++;
      if (i == 26) {
        i = 0;
        break;
      }
    }

    while (1) {
      if (tmp == this->digit[i])
        text += DIGIT[i];
      i++;
      if (i == 10) {
        i = 0;
        break;
      }
    }

    // 특수문자를 발견하면 text에 더해준다
    if (tmp == this->slash)
      text += '/';
    else if (tmp == this->question)
      text += '?';
    else if (tmp == this->comma)
      text += ',';
    else if (tmp == this->period)
      text += '.';
    else if (tmp == this->plus)
      text += '+';
    else if (tmp == this->equal)
      text += '=';

    // "   " 3칸의 빈칸이 띄어쓰기를 의미하므로 이를 발견하면 현재 위치(last)와 비교해서 문장을 띄울 타이밍에 한 칸 띄어쓴다
    space = morse.find("   ", last);
    if(space == last)
      text += " ";

    // 다음 루프를 위해 first에 last를 넣는다
    first = last + 1;
  }
}


int main(int argc, const char *argv[]) {
  Morse m;
  string sentence;
  string Mor;
  string Sen;

  cout << "아래에 영문 텍스트를 입력하세요. 모스 부호로 바꿉니다" << endl;
  getline(cin, sentence, '\n');
  m.text2Morse(sentence, Mor);
  cout << Mor << endl;

  cout << "모스 부호를 다시 영문 텍스트로 바꿉니다" << endl;
  m.morse2Text(Mor, Sen);
  cout << Sen << endl;
  return 0;
}



------------------------------------------------------
/*
 *	c++ ==> 객체지향 p211 11, 겜블링 게임을 만들어서 두 플레이어가 엔터를 칠 때마다 0~2의 숫자가 나와서 일치하면 이기는 게임을 만들어본 코드
 */	
#include <iostream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

// 플레이어 클래스
class Player{
  string name;

 public:
  void setName(string name);
  string getName();
};

// 게임 전체를 담당하는 클래스
class GamblingGame{
  Player *p;

 public:
  GamblingGame();
  void setPlayer(Player p1, Player p2);
  void run();
  bool isWin(int arr[]);
  int randomGenerate();
};

// 2명의 플레이어 객체를 초기화하는 함수
GamblingGame::GamblingGame(){
  p = new Player[2];
}

// 3개의 숫자가 모두 일치하면 true를 반환하는 함수
bool GamblingGame::isWin(int arr[]){
  if(arr[0] == arr[1])
    if(arr[1] == arr[2])
      return true;
  return false;
}

// 2명의 플레이어를 세팅하는 함수
void GamblingGame::setPlayer(Player p1, Player p2){
  p[0] = p1;
  p[1] = p2;
}

// 게임 시작 함수
void GamblingGame::run(){
  int gameArray[3] = {0};

  // 무한루프를 돌면서 2명의 플레이어가 엔터를 누를때마다 겜블링 숫자를 받는다
  while (1){
    cout << p[0].getName()	<<": <Enter>";
    cin.get();
    gameArray[0] = randomGenerate();
    gameArray[1] = randomGenerate();
    gameArray[2] = randomGenerate();

    if(isWin(gameArray)){
      cout << gameArray[0] << "     " << gameArray[1] << "    " << gameArray[2] << "   " << p[0].getName() << "님 승리!!" << endl;
      exit(0);
    }
    else
      cout << gameArray[0] << "     " << gameArray[1] << "    " << gameArray[2] << "   아쉽군요!" << endl;


    cout << p[1].getName()	<<": <Enter>";
    cin.get();
    gameArray[0] = randomGenerate();
    gameArray[1] = randomGenerate();
    gameArray[2] = randomGenerate();

    if(isWin(gameArray)){
      cout << gameArray[0] << "     " << gameArray[1] << "    " << gameArray[2] << "   " << p[1].getName() << "님 승리!!" << endl;
      exit(0);
    }
    else
      cout << gameArray[0] << "     " << gameArray[1] << "    " << gameArray[2] << "   아쉽군요!" << endl;
  }
}

// 난수를 리턴하는 함수
int GamblingGame::randomGenerate(){
  int tmp;
  tmp = rand() % 3;
  return tmp;
}

string Player::getName(){
  return this->name;
}

void Player::setName(string name){
  this->name = name;
}

int main(int argc, const char *argv[]){
  // 난수 생성용 코드
  srand((unsigned)time(0));
  GamblingGame gg;
  Player p1;
  Player p2;
  string tmp;

  cout << "***** 갬블링 게임을 시작합니다. *****" << endl;
  cout << "첫번째 선수 이름>> ";
  cin >> tmp;
  p1.setName(tmp);

  cout << "두번째 선수 이름>> ";
  cin >> tmp;
  cin.ignore();
  p2.setName(tmp);

  gg.setPlayer(p1,p2);
  gg.run();
  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p305 2, 디폴트 매개변수와 생성자를 활용해 id와 이름, 몸무게를 받는 코드
 * 							디폴트매개변수 선언은 클래스 안에서만 해줘야한다!
 */
#include <iostream>
#include <string>
using namespace std;

class Person{
  int id;
  string name;
  double weight;

 public:
  Person(int id = 1, string name = "Grace", double weight= 20.5);
  void show() { cout << id << ' ' << weight << ' ' << name << endl; }
}; 

Person::Person(int id, string name, double weight){
  this->id = id;
  this->name = name;
  this->weight = weight;
}

int main(int argc, const char *argv[]){
  Person grace, ashley(2, "Ashley"), helen(3, "Helen", 32.5);
  grace.show();
  ashley.show();
  helen.show();

  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p210 10, 영어 문장의 글자 수를 입력받아서 문장에 포함된 알파벳의 개수만큼 histogram 히스토그램을 생성하는 Histogram 클래스를 생성하고 이를 사용한 코드
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/regex.hpp>

// regex를 사용하기 위해 boost를 추가해준다
using namespace std;
using namespace boost;

class Histogram{
  string sentence;

 public:
  Histogram(string str) : sentence(str) {
    sentence += '\n';
  }

  void put(string str);
  void putc(char ch);
  void print();
};

void Histogram::put(string str){
  this->sentence += str;
}

void Histogram::putc(char ch){
  string oneWord(1, ch);
  this->sentence += oneWord;
}

void Histogram::print(){
  int numAlpha = 0;
  int len = 0;
  int spaceLen = 0;
  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
  char star = '*';

  cout << this->sentence << endl;

  // 대문자를 소문자로 바꿔주는 구문!
  transform(this->sentence.begin(), this->sentence.end(), this->sentence.begin(), ::tolower);

  len = this->sentence.length();

  // regex 정규표현식을 사용해서 특수문자의 갯수만큼 빼준다
  regex rx("[^a-zA-z]");

  // 알파벳을 제외한 나머지 특수문자의 개수를 세는 코드!
  int match_count(distance(sregex_iterator(this->sentence.begin(), this->sentence.end(), rx), sregex_iterator()));

  len -= match_count;

  cout << "총 알파벳 개수 : " << len << endl;

  // count 함수를 사용해 알파벳의 갯수를 리턴한다
  a = count(sentence.begin(), sentence.end(), 'a');
  b = count(sentence.begin(), sentence.end(), 'b');
  c = count(sentence.begin(), sentence.end(), 'c');
  d = count(sentence.begin(), sentence.end(), 'd');
  e = count(sentence.begin(), sentence.end(), 'e');
  f = count(sentence.begin(), sentence.end(), 'f');
  g = count(sentence.begin(), sentence.end(), 'g');
  h = count(sentence.begin(), sentence.end(), 'h');
  i = count(sentence.begin(), sentence.end(), 'i');
  j = count(sentence.begin(), sentence.end(), 'j');
  k = count(sentence.begin(), sentence.end(), 'k');
  l = count(sentence.begin(), sentence.end(), 'l');
  m = count(sentence.begin(), sentence.end(), 'm');
  n = count(sentence.begin(), sentence.end(), 'n');
  o = count(sentence.begin(), sentence.end(), 'o');
  p = count(sentence.begin(), sentence.end(), 'p');
  q = count(sentence.begin(), sentence.end(), 'q');
  r = count(sentence.begin(), sentence.end(), 'r');
  s = count(sentence.begin(), sentence.end(), 's');
  t = count(sentence.begin(), sentence.end(), 't');
  u = count(sentence.begin(), sentence.end(), 'u');
  v = count(sentence.begin(), sentence.end(), 'v');
  w = count(sentence.begin(), sentence.end(), 'w');
  x = count(sentence.begin(), sentence.end(), 'x');
  y = count(sentence.begin(), sentence.end(), 'y');
  z = count(sentence.begin(), sentence.end(), 'z');

  cout << "a(" << a <<") " << string(a,star) << endl;
  cout << "b(" << b <<") " << string(b,star) << endl;
  cout << "c(" << c <<") " << string(c,star) << endl;
  cout << "d(" << d <<") " << string(d,star) << endl;
  cout << "e(" << e <<") " << string(e,star) << endl;
  cout << "f(" << f <<") " << string(f,star) << endl;
  cout << "g(" << g <<") " << string(g,star) << endl;
  cout << "h(" << h <<") " << string(h,star) << endl;
  cout << "i(" << i <<") " << string(i,star) << endl;
  cout << "j(" << j <<") " << string(j,star) << endl;
  cout << "k(" << k <<") " << string(k,star) << endl;
  cout << "l(" << l <<") " << string(l,star) << endl;
  cout << "m(" << m <<") " << string(m,star) << endl;
  cout << "n(" << n <<") " << string(n,star) << endl;
  cout << "o(" << o <<") " << string(o,star) << endl;
  cout << "p(" << p <<") " << string(p,star) << endl;
  cout << "q(" << q <<") " << string(q,star) << endl;
  cout << "r(" << r <<") " << string(r,star) << endl;
  cout << "s(" << s <<") " << string(s,star) << endl;
  cout << "t(" << t <<") " << string(t,star) << endl;
  cout << "u(" << u <<") " << string(u,star) << endl;
  cout << "v(" << v <<") " << string(v,star) << endl;
  cout << "w(" << w <<") " << string(w,star) << endl;
  cout << "x(" << x <<") " << string(x,star) << endl;
  cout << "y(" << y <<") " << string(y,star) << endl;
  cout << "z(" << z <<") " << string(z,star) << endl;
}

int main(int argc, const char *argv[])
{
  Histogram elvisHisto("Wise men say, only fools rush in But I can't help. ");
  elvisHisto.put("falling in love with you");
  elvisHisto.putc('-');
  elvisHisto.put("Elvis Presley");
  elvisHisto.print();

  return 0;
}




------------------------------------------------------
/*
  c++ ==> 객체지향 p209 9, Circle, CircleManager 클래스를 만들고 원의 이름과 반지름을 입력한 다음 검색을 통해 원하는 결과를 출력하는 코드
*/
#include <iostream>
#include <string>
using namespace std;

static const double PI = 3.14159;
static int index = 0;

class Circle{
  int radius;
  string name;

 public:
  void setCircle(string name, int radius);
  double getArea();
  string getName();
};

// Circle 클래스를 관리하는 CircleManager 객체 선언
class CircleManager{
  Circle *p;
  int size;

 public:
  CircleManager(int size);
  ~CircleManager();
  void setCircle(string name, int radius);
  void searchByName(string name);
  void searchByArea(int area);
};


void Circle::setCircle(string name, int radius){
  this->name = name;
  this->radius = radius;
}

double Circle::getArea(){
  return this->radius * this->radius * PI;
}

string Circle::getName(){
  return this->name;
}

// 원의 개수를 입력받으면 개수만큼의 Circle 객체를 생성한다
CircleManager::CircleManager(int size)
    : size(size){
  p = new Circle[this->size];
}

// 소멸자에서 Circle 객체배열을 제거해준다
CircleManager::~CircleManager(){
  delete[] p;
}

// Circle 객체배열에 값을 입력하는 함수
void CircleManager::setCircle(string name, int radius){
  p[index].setCircle(name, radius);
  index++;
}

// 이름을 검색해서 출력하는 함수
void CircleManager::searchByName(string name){
  int findIndex = 0;

  while (1){
    if (p[findIndex].getName() == name)
      break;

    if(findIndex > 1000){
      break;
    }
    findIndex++;
  }
  cout << p[findIndex].getName() << "의 면적은 " << p[findIndex].getArea() << endl;
}

// 원의 넓이를 검색해서 출력하는 함수
void CircleManager::searchByArea(int area){
  int findIndex = 0;
  int i = 0;
  int findIndexArray[1000] = {0};

  while (1){
    if (p[findIndex].getArea() >= area){
      findIndexArray[i] = findIndex;
      i++;
    }
    if(findIndex > 1000){
      break;
    }
    findIndex++;
  }

  for (int j = 0; j < i - 1 ; j++) {
    cout << p[findIndexArray[j]].getName() << "의 면적은 " << p[findIndexArray[j]].getArea() << endl;
  }
}


int main(int argc, char *argv[]){
  int numOfCircle;
  int fIndex;
  int lastIndex;
  double circleArea;
  string tmp;
  string circleName;


  cout << "원의 개수 >> ";
  cin >> numOfCircle;
  cin.ignore();

  CircleManager cm(numOfCircle);

  for (int i = 0; i < numOfCircle ; i++) {
    cout << "원 " << i+1 << "의 이름과 반지름 >> ";
    getline(cin, tmp, '\n');

    lastIndex = tmp.at(tmp.length() - 1);
    fIndex = tmp.find(' ' , 0);
    cm.setCircle(tmp.substr(0,fIndex), stoi(tmp.substr(fIndex,lastIndex)));
  }

  cout << "검색하고자 하는 원이 이름 >> ";
  cin >> circleName;
  cm.searchByName(circleName);

  cout << "최소 면적을 정수로 입력하세요 >> ";
  cin >> circleArea;
  cout << circleArea << "보다 큰 원을 검색합니다" << endl;
  cm.searchByArea(circleArea);

  return 0;
}




------------------------------------------------------
/*
  c++ ==> 객체지향 p208 8, Person과 Family 클래스를 만들고 각각의 이름을 받아 출력하는 코드
*/
#include <iostream>
#include <string>
using namespace std;

static int numOfFamily = 0;

class Person{
  string name;

 public:
  Person() {}
  Person(string name) : name(name) {}
  void setName(string name);
  string getName() { return name;}
};

class Family{
  Person *p;
  string familyName;
  int size;
  int *index;

 public:
  Family(string name, int size);
  void show();
  void setName(int index, string name);
  ~Family();
};

void Person::setName(string name){
  this->name = name;
}

Family::Family(string name, int size)
    :familyName(name) , size(size) {

  // p와 index 객체를 3개 길이의 배열로 초기화시킨다
  this->p = new Person[3];
  this->index = new int[3];
}

// 소멸자에 배열에 대한 처리를 해줘야한다
Family::~Family() {
  delete[] p;
  delete[] index;
}

void Family::show(){
  cout << p[0].getName() << "   " << p[1].getName() << "   " << p[2].getName() << endl;
}

void Family::setName(int index, string name){
  this->index[numOfFamily] = index;
  this->p[numOfFamily].setName(name);
  numOfFamily++;
}

int main(int argc, char *argv[]) {
  Family *simpson = new Family("Simpson", 3);
  simpson->setName(0, "Mr. Simpson");
  simpson->setName(1, "Mrs. Simpson");
  simpson->setName(2, "Bart Simpson");

  cout << "Simpson 가족은 다음과 같이 3명 입니다" << endl;
  simpson->show();
  delete simpson;

  return 0;
}




------------------------------------------------------
/*
 *	c++ ==> 객체지향 p207 7, Person 클래스에서 이름과 전화번호를 받고 이를 입력받아 출력하는 코드
 */
#include <iostream>
#include <string>
using namespace std;

class Person{
  string name;
  string tel;

 public:
  Person() {}
  string getName() { return name; }
  string getTel() { return tel; }
  void set(string name, string tel);
};

void Person::set(string name, string tel){
  this->name = name;
  this->tel = tel;
}

int main(int argc, const char *argv[]){
  int i = 0;
  Person *p = new Person[3];
  string str[3];
  string name;

  cout << "이름과 전화번호를 입력해 주세요" << endl;
  cout << "사람 1>> ";
  getline(cin, str[0], '\n');
  cout << "사람 2>> ";
  getline(cin, str[1], '\n');
  cout << "사람 3>> ";
  getline(cin, str[2], '\n');

  // 이름과 전화번호의 칸만큼 substr로 구분해서 받아들인다
  // 한글은 한 글자당 3비트씩 먹어서 substr로 0,9까지 자른다
  p[0].set(str[0].substr(0,9), str[0].substr(10,13));
  p[1].set(str[1].substr(0,9), str[1].substr(10,13));
  p[2].set(str[2].substr(0,9), str[2].substr(10,13));

  cout << "모든 사람의 이름은 " << p[0].getName() << ", " << p[1].getName() << ", " << p[2].getName() << endl;
  cout << "전화번호를 검색합니다. 이름을 입력하세요 >> ";
  cin >> name;

  for (i = 0; i < 3; i++)
    if (name == p[i].getName())
      break;

  cout << "전화번호는 " << p[i].getTel();
  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p207 6, Circle의 객체의 갯수를 동적할당 받아 원의 넓이를 구하는 코드
 */
#include <iostream>

#define PI 3.14159
using namespace std;

class Circle {
  int radius;

 public:
  void setRadius(int radius);
  double getArea();
};

void Circle::setRadius(int radius) {
  this->radius = radius;
}

double Circle::getArea() {
  return this->radius * this->radius * PI;
}

int main(int argc, const char *argv[]) {
  int numCircle;
  int rad;
  int count = 0;
  cout << "원의 개수 >> ";
  cin >> numCircle;

  // 동적으로 Circle 객체의 수를 지정하는 코드!
  Circle *c = new Circle[numCircle];

  for (int i = 0; i < numCircle; i++){
    cout << "원" << i+1 << "의 반지름 >> ";
    cin >> rad;
    c[i].setRadius(rad);
  }

  for (int j = 0; j < numCircle; j++){
    if (c[j].getArea() >= 100)
      count++;
  }

  cout << "면적이 100보다 큰 원은 " << count << "개 입니다" << endl;
  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p205 3, string 클래스를 이용하여 사용자가 입력한 영문 한 줄을 글자하나만 랜덤하게 수정하는 코드
 */
#include <iostream>
#include <string>
#include <random>
#include <ctime>
using namespace std;

// 랜덤한 문자 하나를 출력하기 위해 선언한 배열
static const char alphanum[] =
                                                               "0123456789"
                                                               "!@#$%^&*"
                                                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                               "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

// 랜덤한 문자 하나를 반환하는 함수
char genRandom()  
{
  return alphanum[rand() % stringLength];
}

class String {
  string sentence;

 public:
  String() {}
  ~String() {}
  void setSentence(string sen);
  void modifyRandomOneWord();
  string getSentence();
  void exitProgram();
};

// 문장을 받아서 저장하는 멤버함수
void String::setSentence(string sen) {
  if (sen == "exit")
    this->exitProgram();

  this->sentence = sen;
}

// 문장의 임의의 한 단어를 바꾸는 멤버함수
void String::modifyRandomOneWord() {
  int index = rand() % sentence.length();
  string r(1, genRandom());

  // 특정한 Index 부분의 1단어를 랜덤한 문자로 바꾼다
  this->sentence.replace(index, 1,r);
}

string String::getSentence() {
  return this->sentence;
}

void String::exitProgram() {
  cout << "Bye! " << endl;
  exit(0);
}

int main() {
  srand((unsigned)time(0));
  String s;
  string tmp;
	
  cout << "아래에 한 줄을 입력하세요 (exit를 입력하면 종료합니다)" << endl;
  while (1) {
    cout << ">> ";
    getline(cin, tmp, '\n');

    s.setSentence(tmp);
    s.modifyRandomOneWord();
    cout << s.getSentence() << endl;
  }
  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p198 open challange, 한글 끝말잇기 게임을 수행하는 코드
 */
#include <iostream>
#include <string>

class Player {
  string name;

 public:
  Player() {}
  void setName(string name);
  string getName();

};

class WordGame{
  string word[2];

 public:
  WordGame() {}
  void startGame();
  void runGame(Player *p, int arrayLen);
  void loseGame(Player p);
};


void WordGame::startGame() {
  cout << "시작하는 단어는 아버지입니다" << endl;
}

void WordGame::runGame(Player *p, int arrayLen){
  int i = 0;
  int j = 0;
  bool isFirst = true;
  string startWord = "아버지";

  while (1){
    cout << p[i].getName() << ">> ";
    cin >> this->word[j];

    /// 첫판인 경우 : 아버지 --> 지oo
    if (i == 0 && isFirst == true)
      if (word[0].at(0) != startWord.at(startWord.length() - 2) || word[0].at(1) != startWord.at(startWord.length() - 1))
        this->loseGame(p[i]);
      else {
        i++;
        j = 1;
        isFirst = false;
        continue;
      }

    /// 두번째 판부터 아래 코드로 동작한다
    if (j == 0) {
      if (word[j].at(0) != word[j+1].at(word[j+1].length()-2) || word[j].at(1) != word[j+1].at(word[j+1].length()-1))
        this->loseGame(p[i]);
      j = 1;
    }
    else if (j == 1) {
      if (word[j].at(0) != word[j - 1].at(word[j - 1].length()-2) || word[j].at(1) != word[j - 1].at(word[j - 1].length()-1))
        this->loseGame(p[i]);
      j = 0;
    }

    i++;
    if (i > arrayLen - 1) i = 0;
  }
}

void WordGame::loseGame(Player p) {
  cout << "틀렸습니다 " << p.getName() << endl;
  exit(0);
}

void Player::setName(string name){
  this->name = name;
}

string Player::getName() {
  return this->name;
}

int main(int argc, const char *argv[]){
  string tmp;
  int numOfPlayer;
  WordGame wg;

  cout << "끝말잇기 게임을 시작합니다" << endl;
  cout << "게임에 참가하는 인원은 몇명입니까? >> ";
  cin >> numOfPlayer;

  Player *p = new Player[numOfPlayer];

  for (int i = 0; i < numOfPlayer; i++){
    cout << "참가자의 이름을 입력하세요. 빈칸 없이 >> ";
    cin >> tmp;
    p[i].setName(tmp);
  }

  /// 끝말잇기 게임을 시작한다
  wg.startGame();
  wg.runGame(p, numOfPlayer);

  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p149 10, RAM을 추상화한 Ram 클래스를 만들어보고 실제로 사용해본 코드
 */
#include <iostream>
#include <string>

class Ram{
  char mem[100 * 1024];
  int size;

 public:
  Ram();
  ~Ram();
  char read(int address);
  void write(int address, char value);
};

Ram::Ram(){
  mem[100 * 1024] = { 0, };
}

Ram::~Ram(){
  cout << "메모리 제거됨" << endl;
}

char Ram::read(int address){
  return mem[address];
}

void Ram::write(int address, char value){
  mem[address] = value;
}


int main(int argc, const char *argv[]){
  Ram ram;
  ram.write(100, 20);
  ram.write(101, 30);
  char res = ram.read(100) + ram.read(101);
  ram.write(102, res);
  cout << "102 번지의 값 = " << (int)ram.read(102) << endl;
  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p147 7, 타원객체 Oval을 만들고 소멸자에 특별한 메세지를 넣어 사용해본 코드
 */
#include <iostream>
#include <string>
using namespace std;

class Oval
{
  int width;
  int height;

 public:
  Oval() : width(1), height(1) {}
  Oval(int w, int h) : width(w), height(h) {}

  int getWidth();
  int getHeight();
  void set(int w, int h);
  void show();
  ~Oval();
};

int Oval::getWidth()
{
  return width;
}

int Oval::getHeight()
{
  return height;
}

void Oval::set(int w, int h)
{
  this->width = w;
  this->height = h;
}

void Oval::show()
{
  cout << "width is : " << this->width << " and height is : " << this->height << endl;
}

Oval::~Oval()
{
  cout << "Oval 소멸 : width = " << this->width << ", height = " << this->height << endl;
}


int main(int argc, const char *argv[])
{
  Oval a, b(3, 4);
  a.set(10, 20);
  a.show();
  cout << b.getWidth() << "," << b.getHeight() << endl;

  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p146 6, int 타입의 정수를 객체화한 Integer 클래스를 작성하고 이를 사용해본 코드
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Integer
{
  int intnum;

 public:
  Integer(int n) : intnum(n) {}
  Integer(string str) : intnum(stoi(str)) {}

  int get(){
    return intnum;
  }
  void set(int a){
    this->intnum = a;
  }
  bool isEven() {
    if (intnum % 2 == 0) return true;
		
    return false;
  }
  bool isOdd() {
    if (intnum % 2 != 0 && (intnum % 3 == 0 || intnum % 5 == 0 || intnum % 7 == 0)) return true;

    return false;
  }
};

int main(int argc, const char *argv[])
{
  Integer n(30);
  cout << n.get() << ' ';
  n.set(50);
  cout << n.get() << ' ';

  Integer m("300");
  cout << m.get() << ' ';
  cout << m.isEven();

  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p145 5, 짝수 또는 홀수 난수만 생성하는 SelectableRandom 클래스를 만들고 이를 사용하는 코드
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class SelectableRandom
{
 private:
  int ranNum;

 public:
  SelectableRandom()
  {
    // 난수를 발생시키는 코드 2줄!
    srand((unsigned)time(0));
    ranNum = rand() % (RAND_MAX + 1);
  }
  int nextOdd();
  int nextEven();
  int nextInRangeOdd(int min, int max);
  int nextInRangeEven(int min, int max);
};

int SelectableRandom::nextOdd()
{
  while (1)
  {
    ranNum = rand() % RAND_MAX;
    if ((ranNum % 3 == 0  || intnum % 5 == 0 || intnum % 7 == 0) && ranNum % 2 != 0 || ranNum == 1) break;
  }
  return ranNum;
}

int SelectableRandom::nextEven()
{
  while (1)
  {
    ranNum = rand() % RAND_MAX;
    if (ranNum % 2 == 0) break;
  }
  return ranNum;
}

int SelectableRandom::nextInRangeOdd(int min, int max)
{
  while (1)
  {
    ranNum = rand() % (max + 1);
    if (ranNum >= min && ((ranNum % 3 == 0 || intnum % 5 == 0 || intnum % 7 == 0) && ranNum % 2 != 0 || ranNum == 1)) break;
  }
  return ranNum;
}

int SelectableRandom::nextInRangeEven(int min, int max)
{
  while (1)
  {
    ranNum = rand() % (max + 1);
    if (ranNum >= min && ranNum % 2 == 0) break;
  }
  return ranNum;
}

int main(int argc, const char *argv[])
{
  SelectableRandom r;
  cout << "-- 0에서 " << RAND_MAX << "까지의 짝수 랜덤 정수 10개--" << endl;

  for (int i = 0; i< 10; i++)
  {
    int n = r.nextEven();
    cout << n << ' ';
  }

  cout << endl << endl << "-- 2에서 " << " 4까지의 홀수 랜덤 정수 10개 --" << endl;

  for (int i = 0; i<10; i++)
  {
    int n = r.nextInRangeOdd(2, 90);
    cout << n << ' ';
  }
  cout << endl;

  return 0;
}




------------------------------------------------------
/*
 * 	c++ ==> 객체지향 p144 3, 랜덤수를 발생시키는 Random 클래스를 만들어서 next(), nextInRange() 함수를 통해 랜덤수를 출력하는 코드
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Random
{
 private:
  int ranNum;

 public:
  Random()
  {
    // 난수를 발생시키는 코드 2줄!
    srand((unsigned)time(0));
    ranNum = rand() % (RAND_MAX + 1);
  }
  int next();
  int nextInRange(int min, int max);
};

int Random::next()
{
  ranNum = rand() % RAND_MAX;
  return ranNum;
}

// 최대 최소가 있는 난수를 발생시키는 함수
int Random::nextInRange(int min, int max)
{
  while (1)
  {
    ranNum = rand() % (max + 1);
    if (ranNum >= min) break;
  }
  return ranNum;
}


int main(int argc, const char *argv[])
{
  Random r;
  cout << "-- 0에서 " << RAND_MAX << "까지의 랜덤 정수 10개--" << endl;

  for (int i = 0; i< 10; i++)
  {
    int n = r.next();
    cout << n << ' ';
  }

  cout << endl << endl << "-- 2에서 " << " 4까지의 랜덤 정수 10개 --" << endl;

  for (int i = 0; i<10; i++)
  {
    int n = r.nextInRange(2, 4);
    cout << n << ' ';
  }
  cout << endl;

  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p144 2, 날짜 클래스 Date를 작성하고 main문을 통해 사용해보는 코드
 */
#include <iostream>
#include <string>

using namespace std;

class Date
{
 private:
  int year;
  int month;
  int day;

 public:
  Date(int y, int m, int d) : year(y), month(m), day(d)
  {}

  Date(string str)
  {
    year = stoi(str.substr(0, 4));
    month = stoi(str.substr(5, 1));
    day = stoi(str.substr(7, 2));
  }

  void show();
  int getYear();
  int getMonth();
  int getDay();
};

void Date::show()
{
  cout << this->year << "년 " << this->month << "월 " << this->day << "일 " << endl;
}

int Date::getYear()
{
  return this->year;
}

int Date::getMonth()
{
  return this->month;
}

int Date::getDay()
{
  return this->day;
}

int main()
{
  Date birth(2014, 3, 20);
  Date indepen("1945/8/15");
	
  indepen.show();
  cout << birth.getYear() << ", " << birth.getMonth() << ", " << birth.getDay() << endl;

  return 0;
}




------------------------------------------------------
/*
 *  c++ ==> 객체지향 p137 open challange, 지수를 표현하는 클래스를 작성해본 코드
 */
@======== Exp.h ==========
                                                                                   class Exp
                                                                                   {
                                                                                    private:
                                                                                     float base;
                                                                                     float exp;
                                                                                     float result;

                                                                                    public:
                                                                                     Exp(float a, float b) : base(a), exp(b)
                                                                                     {}

                                                                                     Exp(float a) : base(a)
                                                                                     {
                                                                                       exp = 1;
                                                                                     }

                                                                                     Exp()
                                                                                     {
                                                                                       base = 1; exp = 1;
                                                                                     }

                                                                                     float getValue();
                                                                                     float getBase();
                                                                                     float getExp();
                                                                                     bool equals(Exp b);
                                                                                   };

@======== main.cpp ==========
#include "Exp.h"
#include <iostream>
#include <string>
#include <cmath>

                                                                                   using namespace std;

float Exp::getBase()
{
  return this->base;
}

float Exp::getExp()
{
  return this->exp;
}

float Exp::getValue()
{
  result = pow(base,exp);
  return this->result;
}

bool Exp::equals(Exp b)
{
  if (this->getValue() == b.getValue())
    return true;

  return false;
}

int main()
{
  Exp a(3, 2);
  Exp b(9);
  Exp c;

  cout << a.getValue() << endl;
  cout << b.getValue() << endl;
  cout << c.getValue() << endl;

  cout << "a의 베이스 " << a.getBase() << ',' << "지수 " << a.getExp() << endl;
	
  if (a.equals(b))
    cout << "Same" << endl;
  else
    cout << "Diff" << endl;

  return 0;
}





------------------------------------------------------
/*
 * c++ ==> 객체지향 p91 14, 영문텍스트를 ;가 입력될때까지 입력받아 글자의 수와 알파벳의 수를 모두 집계해서 히스토그램 histogram을 그려주는 코드
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, const char *argv[])
{
  string sentence;
  int numAlpha = 0;
  int len = 0;
  int spaceLen = 0;
  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
  char star = '*';

  cout << "영문 텍스트를 입력하세요. 히스토그램을 그립니다" << endl;
  cout << "텍스트의 끝은 ; 입니다. 10000개까지 가능합니다" << endl;
  getline(cin, sentence, ';');
	
  // 대문자를 소문자로 바꿔주는 구문!
  transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);

  // 총 글자의 수 = 총 문장 단어수 - 스페이스의 갯수로 구한다
  len = sentence.length();
  spaceLen = count(sentence.begin(), sentence.end(), ' ');
  numAlpha = len - spaceLen;

  cout << "총 알파벳 개수 : " << numAlpha << endl;

  // count 함수를 사용해 알파벳의 갯수를 리턴한다
  a = count(sentence.begin(), sentence.end(), 'a');
  b = count(sentence.begin(), sentence.end(), 'b');
  c = count(sentence.begin(), sentence.end(), 'c');
  d = count(sentence.begin(), sentence.end(), 'd');
  e = count(sentence.begin(), sentence.end(), 'e');
  f = count(sentence.begin(), sentence.end(), 'f');
  g = count(sentence.begin(), sentence.end(), 'g');
  h = count(sentence.begin(), sentence.end(), 'h');
  i = count(sentence.begin(), sentence.end(), 'i');
  j = count(sentence.begin(), sentence.end(), 'j');
  k = count(sentence.begin(), sentence.end(), 'k');
  l = count(sentence.begin(), sentence.end(), 'l');
  m = count(sentence.begin(), sentence.end(), 'm');
  n = count(sentence.begin(), sentence.end(), 'n');
  o = count(sentence.begin(), sentence.end(), 'o');
  p = count(sentence.begin(), sentence.end(), 'p');
  q = count(sentence.begin(), sentence.end(), 'q');
  r = count(sentence.begin(), sentence.end(), 'r');
  s = count(sentence.begin(), sentence.end(), 's');
  t = count(sentence.begin(), sentence.end(), 't');
  u = count(sentence.begin(), sentence.end(), 'u');
  v = count(sentence.begin(), sentence.end(), 'v');
  w = count(sentence.begin(), sentence.end(), 'w');
  x = count(sentence.begin(), sentence.end(), 'x');
  y = count(sentence.begin(), sentence.end(), 'y');
  z = count(sentence.begin(), sentence.end(), 'z');
	
  cout << "a(" << a <<") " << string(a,star) << endl;
  cout << "b(" << b <<") " << string(b,star) << endl;
  cout << "c(" << c <<") " << string(c,star) << endl;
  cout << "d(" << d <<") " << string(d,star) << endl;
  cout << "e(" << e <<") " << string(e,star) << endl;
  cout << "f(" << f <<") " << string(f,star) << endl;
  cout << "g(" << g <<") " << string(g,star) << endl;
  cout << "h(" << h <<") " << string(h,star) << endl;
  cout << "i(" << i <<") " << string(i,star) << endl;
  cout << "j(" << j <<") " << string(j,star) << endl;
  cout << "k(" << k <<") " << string(k,star) << endl;
  cout << "l(" << l <<") " << string(l,star) << endl;
  cout << "m(" << m <<") " << string(m,star) << endl;
  cout << "n(" << n <<") " << string(n,star) << endl;
  cout << "o(" << o <<") " << string(o,star) << endl;
  cout << "p(" << p <<") " << string(p,star) << endl;
  cout << "q(" << q <<") " << string(q,star) << endl;
  cout << "r(" << r <<") " << string(r,star) << endl;
  cout << "s(" << s <<") " << string(s,star) << endl;
  cout << "t(" << t <<") " << string(t,star) << endl;
  cout << "u(" << u <<") " << string(u,star) << endl;
  cout << "v(" << v <<") " << string(v,star) << endl;
  cout << "w(" << w <<") " << string(w,star) << endl;
  cout << "x(" << x <<") " << string(x,star) << endl;
  cout << "y(" << y <<") " << string(y,star) << endl;
  cout << "z(" << z <<") " << string(z,star) << endl;

  return 0;
}







------------------------------------------------------
/*
 * c++ ==> 객체지향 p89 11, 끝수를 입력받아 1부터 끝수까지 합을 출력하는 코드
 */
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
  int k, n = 0;
  int sum =0;

  cout << "끝 수를 입력하세요>> ";
  cin >> n;

  for(k =1 ; k <= n ; k++)
    sum += k;
	
  cout << "1에서 " << n << "까지의 합은 " << sum << " 입니다" << endl;

  return 0;
}






------------------------------------------------------
/*
  c++ ==> 객체지향 p88 8, 한 라인에 이름을 ;로 구분해서 받고
  각각 끊어낸 다음 가장 긴 이름을 출력하는 코드
*/
#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
  string name;
  string man[5];
  string finalName;
  int i = 0;
  int count = 0;

  cout << "5명의 이름을 ';'으로 구분하여 입력하세요" << endl;
  cout << ">> ";
  cin >> name;

  int startIndex = 0;
  int fIndex = 0;
  while (1)
  {
    fIndex = name.find(';', startIndex);
	
    if (fIndex == -1)  break;

    count = fIndex - startIndex;
    man[i++] = name.substr(startIndex, count);
    startIndex = fIndex + 1;

    if (i > 4) break;
  }
	
  for (int i = 0; i < 5 - 1; i++)
  {
    if (man[i].length() > man[i + 1].length())
      finalName = man[i];
    else
      finalName = man[i + 1];

  }

  cout << "가장 긴 이름은 " << finalName << endl;
  return 0;
}



------------------------------------------------------
/*
  c++ ==> 객체지향 p88 7, yes가 입력되는 종료되는 프로그램 작성하기
*/
#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
  char str[] = { 0 };

  while (1)
  {
    cout << "종료하고 싶으면 yes를 입력하세요 >> ";
    cin.getline(str, 10);

    if (strcmp(str, "yes") == 0)
    {
      exit(0);
    }
  }
  return 0;
}

------------------------------------------------------
/*
  c++ ==> 객체지향, p206 #6 동적으로 Circle 객체를 할당받아 원의 반지름을 입력하고
  너비가 100 이상인 원의 개수를 출력하는 코드
*/
#include <iostream>

using namespace std;

class Circle
{
  int radius;

 public:
  void setRadius(int radius);
  double getArea();
};

void Circle::setRadius(int radius)
{
  this->radius = radius;
}

double Circle::getArea()
{
  return this->radius * this->radius;
}

int main(int argc, char *argv[])
{
  int num = 0;

  cout << "원의 갯수를 입력해주세요 : " ;
  cin >> num;

  Circle *cp = new Circle[num];
  int *rad = new int[num];

  for (int i = 0; i < num; i++)
  {
    cout << "c" << i << "의 반지름 >> ";
    cin >> rad[i];
  }

  for (int i = 0; i < num; i++)
  {
    cp[i].setRadius(rad[i]);
  }

  int count = 0;

  for (int i = 0; i < num ; i++)
  {
    if (cp[i].getArea() > 100)
    {
      count++;
    }
  }
  cout << "면적이 100보다 큰 원은 " << count << " 개 입니다"<< endl;

  return 0;
}

--------------------------------------------------------------------------
/*
  c++ ==> 객체지향, p206 #5 Circle 객체를 생성해서 setradius, getarea 함수를 구현해보고
  원을 3개 선언해서 100보다 큰 원을 찾는 코드
*/
#include <iostream>

using namespace std;

class Circle
{
  int radius;

 public:
  void setRadius(int radius);
  double getArea();
};

void Circle::setRadius(int radius)
{
  this->radius = radius;
}

double Circle::getArea()
{
  return this->radius * this->radius;
}

int main(int argc, char *argv[])
{
  Circle c1;
  Circle c2;
  Circle c3;

  int rad, rad2, rad3;
  int count = 0;

  cout << "c1의 반지름 >> ";
  cin >> rad;
  cout << "c2의 반지름 >> ";
  cin >> rad2;
  cout << "c3의 반지름 >> ";
  cin >> rad3;

  c1.setRadius(rad);
  c2.setRadius(rad2);
  c3.setRadius(rad3);

  if(c1.getArea() > 100)
    count++;

  if(c2.getArea() > 100)
    count++;

  if(c3.getArea() > 100)
    count++;

  cout << "면적이 100보다 큰 원은 " << count << " 개 입니다"<< endl;

  return 0;
}
