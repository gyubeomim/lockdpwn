/*
  c++ ==> prject 슈퍼마켓 상품 관리 프로그램 코드 for Windows OS

  http://www.codeincodeblock.com/2012/01/mini-project-supermarket-billing-system.html
*/
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>

using namespace std;

// 전역변수 선언
int k=7;
int r=0;
int flag=0;

COORD coord = {0, 0};

ofstream fout;
ifstream fin;


// 콘솔창 이동
void gotoxy(int x, int y)
{
  COORD coord;

  coord.X = x;
  coord.Y = y;

  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


// date 구조체 선언
struct date
{
  int mm;
  int dd;
  int yy;
};


// item 클래스 선언
class item
{
  int itemno;
  char name[25];
  date d;

 public:

  void add()
  {
    cout<<"\n\n\tItem No: ";
    cin>>itemno;

    cout<<"\n\n\tName of the item: ";
    cin>>name;

    cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
    cin>>d.mm>>d.dd>>d.yy;
  }


  void show()
  {
    cout<<"\n\tItem No: ";
    cout<<itemno;

    cout<<"\n\n\tName of the item: ";
    cout<<name;

    cout<<"\n\n\tDate : ";
    cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
  }


  void report()
  {
    gotoxy(3,k);

    cout<<itemno;

    gotoxy(13,k);

    puts(name);
  }


  int retno()
  {
    return(itemno);
  }

};


// amount 클래스 선언 also known as 'amt'
class amount: public item
{
 private:

  float price;
  float qty;
  float tax;
  float gross;
  float dis;
  float netamt;



 public:

  void add();
  void show();
  void report();
  void calculate();
  void pay();

  float retnetamt()
  {
    return(netamt);
  }

}amt;



void amount::add()
{
  item::add();
  cout<<"\n\n\tPrice: ";
  cin>>price;

  cout<<"\n\n\tQuantity: ";
  cin>>qty;

  cout<<"\n\n\tTax percent: ";
  cin>>tax;

  cout<<"\n\n\tDiscount percent: ";
  cin>>dis;

  calculate();

  fout.write( (char *)&amt, sizeof(amt) );
  fout.close();
}



void amount::calculate()
{
  gross = price + (price * ( tax/100 ));

  netamt= qty * ( gross - (gross * (dis/100)) );
}




void amount::show()
{

  fin.open("itemstore.dat",ios::binary);
  fin.read( (char*)&amt, sizeof(amt) );

  item::show();


  cout << "\n\n\tNet amount: ";
  cout<<netamt;

  fin.close();

}



void amount::report()
{
  item::report();

  gotoxy(23,k);
  cout<<price;

  gotoxy(33,k);
  cout<<qty;

  gotoxy(44,k);
  cout<<tax;

  gotoxy(52,k);
  cout<<dis;

  gotoxy(64,k);
  cout<<netamt;

  k=k+1;

  // if k is 50..? 이게 무슨 소리지
  if(k==50)
  {
    gotoxy(25,50);

    cout<<"PRESS ANY KEY TO CONTINUE...";
    getch();

    k=7;

    system("cls");

    gotoxy(30,3);
    cout<<" ITEM DETAILS ";

    gotoxy(3,5);
    cout<<"NUMBER";

    gotoxy(13,5);
    cout<<"NAME";

    gotoxy(23,5);
    cout<<"PRICE";

    gotoxy(33,5);
    cout<<"QUANTITY";

    gotoxy(44,5);
    cout<<"TAX";

    gotoxy(52,5);
    cout<<"DEDUCTION";

    gotoxy(64,5);
    cout<<"NET AMOUNT";
  }
}



void amount::pay()
{
  show();

  cout<<"\n\n\n\t\t*********************************************";
  cout<<"\n\t\t                 DETAILS                  ";
  cout<<"\n\t\t*********************************************";
  cout<<"\n\n\t\tPRICE                     :"<<price;
  cout<<"\n\n\t\tQUANTITY                  :"<<qty;
  cout<<"\n\t\tTAX PERCENTAGE              :"<<tax;
  cout<<"\n\t\tDISCOUNT PERCENTAGE         :"<<dis;
  cout<<"\n\n\n\t\tNET AMOUNT              :Rs."<<netamt;
  cout<<"\n\t\t*********************************************";
}




// MAIN 함수 시작
int main()
{
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);

  // 2자리수까지만 표기합니다(?)
  cout<<setprecision(2);

  // 바이너리 형식으로 출력함수를 사용할 목적으로 엽니다(?)
  // open binary mode, open for output operations
  fstream tmp("temp.dat",ios::binary|ios::out);


menu:
  int ch;
  int ff;
  float gtotal;

  system("cls");

  gotoxy(25,2);
  cout<<"Super Market Billing ";

  gotoxy(25,3);
  cout<<"===========================\n\n";
  cout<<"\n\t\t1.Bill Report\n\n";
  cout<<"\t\t2.Add/Remove/Edit Item\n\n";
  cout<<"\t\t3.Show Item Details\n\n";
  cout<<"\t\t4.Exit\n\n";
  cout<<"\t\tPlease Enter Required Option: ";

  cin>>ch;

  switch(ch)
  {
    case 1:
    ss:
      int cho;

      system("cls");

      gotoxy(25,2);
      cout<<"Bill Details";

      gotoxy(25,3);
      cout<<"================\n\n";
      cout<<"\n\t\t1.All Items\n\n";
      cout<<"\t\t2.Back to Main menu\n\n";
      cout<<"\t\tPlease Enter Required Option: ";

      cin>>cho;


      // 1. All Items를 누를 경우
      if(cho==1)
      {
        system("cls");

        gotoxy(30,3);
        cout<<" BILL DETAILS ";

        gotoxy(3,5);
        cout<<"ITEM NO";

        gotoxy(13,5);
        cout<<"NAME";

        gotoxy(23,5);
        cout<<"PRICE";

        gotoxy(33,5);
        cout<<"QUANTITY";

        gotoxy(44,5);
        cout<<"TAX %";

        gotoxy(52,5);
        cout<<"DISCOUNT %";

        gotoxy(64,5);
        cout<<"NET AMOUNT";

        fin.open("itemstore.dat",ios::binary);

        // itemstore.dat 파일이 없는 경우
        if(!fin)
        {
          cout<<"\n\nFile Not Found...";
          goto menu;
        }

        // 첫줄로 갑니다
        fin.seekg(0);

        // float gtotal; Grand Total
        gtotal=0;


        // 파일이 끝날때까지 읽습니다
        while(!fin.eof())
        {

          fin.read( (char*)&amt, sizeof(amt) );

          if(!fin.eof())
          {
            amt.report();

            gtotal+=amt.retnetamt();

            ff=0;
          }

          if(ff!=0)
          {
            gtotal=0;
          }

        }

        gotoxy(17,k);
        cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;

        getch();

        fin.close();
      }

      // 2번을 누른경우 메뉴로 갑니다
      if(cho==2)
      {
        goto menu;
      }

      // 아니면 다시 ss로 갑니다
      goto ss;



    case 2:
    db:
      int apc;

      system("cls");

      gotoxy(25,2);
      cout<<"Bill Editor";

      gotoxy(25,3);
      cout<<"=================\n\n";
      cout<<"\n\t\t1.Add Item Details\n\n";
      cout<<"\t\t2.Edit Item Details\n\n";
      cout<<"\t\t3.Delete Item Details\n\n";
      cout<<"\t\t4.Back to Main Menu ";

      cin>>apc;

      switch(apc)
      {

        // 1. 상품 추가
        case 1:
          fout.open("itemstore.dat",ios::binary|ios::app);
          amt.add();

          cout<<"\n\t\tItem Added Successfully!";
          getch();

          goto db;


          // 2. 상품 정보 변경
        case 2:
          int ino;

          flag=0;
          cout<<"\n\n\tEnter Item Number to be Edited :";

          cin>>ino;

          fin.open("itemstore.dat",ios::binary);
          fout.open("itemstore.dat",ios::binary|ios::app);

          if(!fin)
          {
            cout<<"\n\nFile Not Found...";
            goto menu;
          }

          // itemstore.dat 파일 첫줄로 갑니다
          fin.seekg(0);

          r=0;


          while(!fin.eof())
          {
            fin.read((char*)&amt,sizeof(amt));

            if(!fin.eof())
            {
              // 상품 번호를 불러옵니다
              int x=amt.item::retno();

              // 상품 번호가 맞을 경우
              if(x==ino)
              {
                flag=1;

                fout.seekp(r*sizeof(amt));

                system("cls");

                cout<<"\n\t\tCurrent Details are\n";
                amt.show();

                cout<<"\n\n\t\tEnter New Details\n";
                amt.add();

                cout<<"\n\t\tItem Details editted";
              }
            }

            r++;
          }


          if(flag==0)
          {
            cout<<"\n\t\tItem No does not exist...Please Retry!";
            getch();
            goto db;
          }

          fin.close();
          getch();
          goto db;



          // 물건 삭제
        case 3:

          flag=0;
          cout<<"\n\n\tEnter Item Number to be deleted :";
          cin>>ino;

          fin.open("itemstore.dat",ios::binary);

          if(!fin)
          {
            cout<<"\n\nFile Not Found...";
            goto menu;
          }

          //fstream tmp("temp.dat",ios::binary|ios::out);
          fin.seekg(0);

          while(fin.read((char*)&amt, sizeof(amt)))
          {
            int x=amt.item::retno();
            if(x!=ino)
              tmp.write((char*)&amt,sizeof(amt));

            else
            {
              flag=1;
            }
          }

          fin.close();
          tmp.close();

          fout.open("itemstore.dat",ios::trunc|ios::binary);

          fout.seekp(0);

          tmp.open("temp.dat",ios::binary|ios::in);

          if(!tmp)
          {
            cout<<"Error in File";
            goto db;
          }

          while( tmp.read((char*)&amt,sizeof(amt)) )
          {
            fout.write((char*)&amt,sizeof(amt));
          }

          tmp.close();

          fout.close();

          if(flag==1)
            cout<<"\n\t\tItem Succesfully Deleted";

          else if (flag==0)
            cout<<"\n\t\tItem does not Exist! Please Retry";

          getch();
          goto db;

        case 4:
          goto menu;

        default: cout<<"\n\n\t\tWrong Choice!!! Retry";
          getch();
          goto db;
      }



    case 3:
      int ino;

      system("cls");

      flag=0;

      cout<<"\n\n\t\tEnter Item Number :";
      cin>>ino;

      fin.open("itemstore.dat",ios::binary);


      if(!fin)
      {
        cout<<"\n\nFile Not Found...\nProgram Terminated!";
        goto menu;
      }

      fin.seekg(0);


      while(fin.read((char*)&amt,sizeof(amt)))
      {
        int x=amt.item::retno();
        if(x==ino)
        {
          amt.pay();
          flag=1;
          break;
        }
      }


      if(flag==0)
      {
        cout<<"\n\t\tItem does not exist....Please Retry!";
      }

      getch();

      fin.close();

      goto menu;



      // 4. 프로그램 종료
    case 4:
      char yn;

      system("cls");

      gotoxy(20,20);
      cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";

      cin>>yn;

      if((yn=='Y')||(yn=='y'))
      {
        gotoxy(12,20);

        system("cls");
        cout<<"************************** THANKS **************************************";

        getch();
        // 종료 코드
        exit(0);
      }

      else if((yn=='N')||(yn=='n'))
      {
        goto menu;
      }

      else
      {
        goto menu;
      }

      // ?. 잘못 누른 경우
    default:
      cout<<"\n\n\t\tWrong Choice....Please Retry!";

      getch();
      goto menu;
  }


  return 0;
} // END MAIN
