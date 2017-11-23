#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define Green SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 10)  
#define White SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7)
#define Yellow SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 14)
#define Red SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 4)

int totalscore[2]={0};        //score 함수를 위한 전역변수

void countdown(void);
void intro_design(void);
void design(void);
int level(int userchoice1);
void gotoxy(int x, int y);
void movement(int random, int random_2, int random_3, int random_4,int  random_5, int x, int y, int userchoice1);
int score(int eye_random, int user[]);
int random_duplication_remove(int random, int random_2, int random_3,int random_4,int random_5);

int  Input_KeyState (int user[]);
void eye_1( int user[], int eye_random);

#define line2doduge +5   //2번째 줄의 두더지 y축 
#define line3doduge +10 // 3번째 줄의 두더지 y축
#define getch _getch

int main()
{
  int userchoice1=0, restart;       //userchoice1 = 유저가 선택한 난이도 값을 넣을 변수
  int random, random_2=0, random_3=0, random_4=0, random_5=0;     //난수 값을 넣을 변수.
  //밑의 if문장으로 인해 random_2,_3는 초기화를 해줌.
  double past;
  time_t start, end;

  srand((unsigned)time(0));

  intro_design();
  system("cls");
  design();
A:    //////////////////////////////////goto A

  gotoxy(26,9);
  printf("난이도 = 아빠 나 해도 돼요?(3)\n");
  gotoxy(26,10);
  printf("난이도 = 한번 놀아 볼까?(6)\n");
  gotoxy(26,11);
  printf("난이도 = 미친거 아니야?(9)\n");
  gotoxy(26,12);
  scanf_s("%d", &userchoice1);
  gotoxy(26,11);
  printf("                                   ");
  gotoxy(26,9);
  printf("                                   ");

  level(userchoice1);     //난이도 함수
  design();
  countdown();
  start = time(NULL);

  do
  {
    end = time(NULL);
    past = difftime(end, start);

    //두더지 머릿수를 시간에 따라 늘려줌. 최대 5개
    random = rand()% userchoice1 +1;
    if(past>=8)
      random_2 = rand()% userchoice1 +1;
    if(past>=18)
      random_3 = rand()% userchoice1 +1;
    if(past>=28 && userchoice1 >= 6)
      random_4 = rand()% userchoice1 +1;
    if(past>=38 && userchoice1 == 9)
      random_5 =rand()% userchoice1 +1;

    random_duplication_remove( random, random_2, random_3,random_4,random_5);
    // x 축 = 10, y 축 = 10
    movement(random, random_2, random_3, random_4, random_5, 10, 10, userchoice1);

    //55초 이상이되면 타이머 색을 초록색으로
    if(past>=55)
    {
      Green;
    }

    gotoxy(27,4);
    //"."앞의 값만 출력,  60부터 -1씩 깎임
    printf("%.lf초",60 - past);
    White;
    gotoxy(34,4);
    //스코어 값을 출력
    printf("%d", totalscore[0]);
    //60초까지
  }while(past <5);

  White;

  system("cls");
  totalscore[1] += totalscore[0];
  gotoxy(27,7);
  printf("점수 = %d\n", totalscore[1]);

  gotoxy(20,10);
  printf("다시 하시겠습니까?(엔터를 눌러주세요.)\n");
  gotoxy(20,11);
  printf("종료는 마이너스 값을 입력해주세요.\n");
  gotoxy(27,12);
  scanf_s("%d", &restart);
  system("cls");
  //전역변수 totalscore 초기화
  totalscore[0] = 0;

  if(restart >= 1)
    //위로 이동.
    goto A;
  else
    return 0;
}

void movement(int random, int random_2, int random_3, int random_4,int  random_5, int x, int y, int userchoice1)
{
  int user[9]={0};
  int doduge_1 = 17, doduge_2 = 27, doduge_3 = 37;
  int eye_random=0;

  Yellow;

  gotoxy(x + doduge_1, y-1 );
  printf(" ___ ");
  gotoxy(x-1 + doduge_1, y );
  printf("(     ) ");

  gotoxy(x + doduge_2, y-1 );
  printf(" ___ ");
  gotoxy(x-1 + doduge_2, y );
  printf("(     ) ");

  gotoxy(x + doduge_3, y-1 );
  printf(" ___ ");
  gotoxy(x-1 + doduge_3, y );
  printf("(     ) ");

  gotoxy(x + doduge_1, y line2doduge -1);
  printf(" ___ ");
  gotoxy(x-1 + doduge_1, y line2doduge  );
  printf("(     ) ");

  gotoxy(x + doduge_2, y line2doduge-1);
  printf(" ___ ");
  gotoxy(x-1 + doduge_2, y line2doduge  );
  printf("(     ) ");

  gotoxy(x + doduge_3, y line2doduge-1);
  printf(" ___ ");
  gotoxy(x-1 + doduge_3, y line2doduge  );
  printf("(     ) ");

  gotoxy(x + doduge_1, y line3doduge-1);
  printf(" ___ ");
  gotoxy(x-1 + doduge_1, y line3doduge );
  printf("(     ) ");

  gotoxy(x + doduge_2, y line3doduge-1);
  printf(" ___ ");
  gotoxy(x-1 + doduge_2, y line3doduge );
  printf("(     ) ");

  gotoxy(x + doduge_3, y line3doduge-1);
  printf(" ___ ");
  gotoxy(x-1 + doduge_3, y line3doduge );
  printf("(     ) ");

  ///////////////////////////////////////////////////////////         " ___ "
  Sleep(100);

  if(random == 1 || random_2 == 1 || random_3 == 1 || random_4==1 || random_5 == 1){
    gotoxy(x + doduge_1, y -1);
    printf(" ___ ");}

  if(random == 2|| random_2 == 2 || random_3 == 2 || random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y -1);
    printf(" ___ ");}

  if(random == 3|| random_2 == 3 || random_3 == 3 || random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y-1 );
    printf(" ___ ");}

  if(random == 4 || random_2 == 4 || random_3 == 4|| random_4==4 || random_5 == 4){
    gotoxy(x + doduge_1, y line2doduge -1);
    printf(" ___ ");}

  if(random == 5 || random_2 == 5 || random_3 == 5 || random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge -1);
    printf(" ___ ");}

  if(random == 6 || random_2 == 6 || random_3 == 6|| random_4==6 || random_5 == 6){
    gotoxy(x + doduge_3, y line2doduge -1);
    printf(" ___ ");}

  if(random == 7 || random_2 == 7 || random_3 == 7|| random_4==7 || random_5 == 7){
    gotoxy(x + doduge_1, y line3doduge -1);
    printf(" ___ ");}

  if(random == 8 || random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8){
    gotoxy(x + doduge_2, y line3doduge -1);
    printf(" ___ ");}

  if(random == 9 || random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9){
    gotoxy(x + doduge_3, y line3doduge -1);
    printf(" ___ ");}
  ////////////////////////////////////////////////////////////////y-1 ,윗부분에  " ___ "



  if(random == 1|| random_2 == 1 || random_3 == 1|| random_4==1 || random_5 == 1){
    gotoxy(x+ doduge_1, y);

    printf("|");
    printf("0 0");
    printf("|");}

  if(random == 2|| random_2 == 2 || random_3 == 2|| random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y)
        ;
    printf("|");
    printf("0 0");
    printf("|");}

  if(random == 3|| random_2 == 3 || random_3 == 3|| random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y);

    printf("|");
    printf("0 0");
    printf("|");}

  if(random == 4|| random_2 == 4 || random_3 == 4|| random_4==4 || random_5 == 4){
    gotoxy(x + doduge_1, y line2doduge);

    printf("|");
    printf("0 0");
    printf("|");}

  if(random == 5|| random_2 == 5 || random_3 == 5|| random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge);

    printf("|");
    printf("0 0");
    printf("|");}

  if(random == 6|| random_2 == 6 || random_3 == 6|| random_4==6 || random_5 == 6){
    gotoxy(x + doduge_3, y line2doduge);

    printf("|");
    printf("0 0");
    printf("|");}

  if(random == 7|| random_2 == 7 || random_3 == 7|| random_4==7 || random_5 == 7){
    gotoxy(x + doduge_1, y line3doduge);

    printf("|");
    printf("0 0");
    printf("|");}

  if(random == 8|| random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8){
    gotoxy(x + doduge_2, y line3doduge);

    printf("|");
    printf("0 0");
    printf("|");}

  if(random == 9 || random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9){
    gotoxy(x + doduge_3, y line3doduge);

    printf("|");
    printf("0 0");
    printf("|");}
  //  ___
  Sleep(100);///////////////////////////////////////////// "|0  0|"     0 0 는 eye_1 함수로 인해 X X가 될 수 있음.


  if(random == 1|| random_2 == 1 || random_3 == 1|| random_4==1 || random_5 == 1){
    gotoxy(x+ doduge_1, y - 2);
    printf(" ___ ");}

  if(random == 2|| random_2 == 2 || random_3 == 2|| random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y - 2);
    printf(" ___ ");}

  if(random == 3|| random_2 == 3 || random_3 == 3|| random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y - 2);
    printf(" ___ ");}

  if(random == 4|| random_2 == 4 || random_3 == 4|| random_4==4 || random_5 == 4){
    gotoxy(x + doduge_1, y line2doduge -2);
    printf(" ___ ");}

  if(random == 5|| random_2 == 5 || random_3 == 5|| random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge -2);
    printf(" ___ ");}

  if(random == 6|| random_2 == 6 || random_3 == 6|| random_4==6 || random_5 == 6){
    gotoxy(x + doduge_3, y line2doduge -2);
    printf(" ___ ");}

  if(random == 7 || random_2 == 7 || random_3 == 7|| random_4==7 || random_5 == 7){
    gotoxy(x + doduge_1, y line3doduge -2);
    printf(" ___ ");}

  if(random == 8|| random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8){
    gotoxy(x + doduge_2, y line3doduge -2);
    printf(" ___ ");}

  if(random == 9|| random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9){
    gotoxy(x + doduge_3, y line3doduge -2);
    printf(" ___ ");}



  Input_KeyState (user);                                                    //숫자패드 값을 입력받음

  if(random == 1|| random_2 == 1 || random_3 == 1|| random_4==1 || random_5 == 1){
    gotoxy(x+ doduge_1, y - 1);

    printf("|");

    eye_random = 1;
    eye_1(user, eye_random);


    printf("|");}

  if(random == 2|| random_2 == 2 || random_3 == 2|| random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y - 1);

    printf("|");

    eye_random = 2;
    eye_1(user, eye_random);


    printf("|");}

  if(random == 3|| random_2 == 3 || random_3 == 3|| random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y - 1);

    printf("|");

    eye_random = 3;
    eye_1(user, eye_random);


    printf("|");}

  if(random == 4|| random_2 == 4|| random_3 == 4|| random_4==4 || random_5 == 4 ){
    gotoxy(x + doduge_1, y line2doduge - 1);

    printf("|");

    eye_random = 4;
    eye_1(user, eye_random);


    printf("|");}

  if(random ==  5|| random_2 == 5 || random_3 ==5|| random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge - 1);

    printf("|");

    eye_random = 5;
    eye_1(user, eye_random);


    printf("|");}

  if(random == 6|| random_2 == 6 || random_3 == 6|| random_4==6 || random_5 == 6)
  {
    gotoxy(x + doduge_3, y line2doduge - 1);

    printf("|");

    eye_random = 6;
    eye_1(user, eye_random);

    printf("|");
  }

  if(random == 7|| random_2 == 7 || random_3 == 7|| random_4==7 || random_5 == 7)
  {
    gotoxy(x + doduge_1, y line3doduge - 1);

    printf("|");

    eye_random = 7;
    eye_1(user, eye_random);

    printf("|");
  }

  if(random == 8|| random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8)
  {
    gotoxy(x + doduge_2, y line3doduge - 1);

    printf("|");

    eye_random = 8;
    eye_1(user, eye_random);

    printf("|");
  }

  if(random == 9|| random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9)
  {
    gotoxy(x + doduge_3, y line3doduge - 1);

    printf("|");

    eye_random = 9;
    eye_1(user, eye_random);

    printf("|");
  }

  if(random == 1|| random_2 == 1 || random_3 == 1|| random_4==1 || random_5 == 1){
    gotoxy(x+ doduge_1, y);
    printf("|   |");}

  if(random == 2|| random_2 == 2 || random_3 == 2|| random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y);
    printf("|   |");}

  if(random == 3|| random_2 == 3 || random_3 == 3|| random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y);
    printf("|   |");}

  if(random == 4|| random_2 == 4 || random_3 == 4|| random_4==4 || random_5 == 4){
    gotoxy(x + doduge_1, y line2doduge);
    printf("|   |");}

  if(random == 5|| random_2 == 5 || random_3 == 5|| random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge);
    printf("|   |");}

  if(random == 6|| random_2 == 6 || random_3 == 6|| random_4==6 || random_5 == 6){
    gotoxy(x + doduge_3, y line2doduge);
    printf("|   |");}

  if(random == 7|| random_2 == 7 || random_3 == 7|| random_4==7 || random_5 == 7){
    gotoxy(x + doduge_1, y line3doduge );
    printf("|   |");}

  if(random == 8|| random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8){
    gotoxy(x + doduge_2, y line3doduge );
    printf("|   |");}

  if(random == 9|| random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9 ){
    gotoxy(x + doduge_3, y line3doduge );
    printf("|   |");}
  //   ___
  Sleep(500); ////////////////////////////////////////  |0  0|
  ///  |     |
  Input_KeyState (user);                          //숫자패드 값을 입력받음

  if(random == 1|| random_2 == 1 || random_3 == 1|| random_4==1 || random_5 == 1){
    gotoxy(x+ doduge_1, y - 2);
    printf("      ");}

  if(random == 2|| random_2 == 2 || random_3 == 2|| random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y - 2);
    printf("      ");}

  if(random == 3|| random_2 == 3 || random_3 == 3|| random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y - 2);
    printf("      ");}

  if(random == 4|| random_2 == 4 || random_3 == 4|| random_4==4|| random_5 == 4){
    gotoxy(x + doduge_1, y line2doduge- 2);
    printf("      ");}

  if(random == 5|| random_2 == 5 || random_3 == 5|| random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge- 2);
    printf("      ");}

  if(random == 6|| random_2 == 6|| random_3 == 6|| random_4==6 || random_5 == 6){
    gotoxy(x + doduge_3, y line2doduge- 2);
    printf("      ");}

  if(random == 7|| random_2 == 7 || random_3 == 7|| random_4==7 || random_5 == 7){
    gotoxy(x + doduge_1, y line3doduge- 2);
    printf("      ");}

  if(random == 8|| random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8){
    gotoxy(x + doduge_2, y line3doduge- 2);
    printf("      ");}

  if(random == 9|| random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9){
    gotoxy(x + doduge_3, y line3doduge- 2);
    printf("      ");}

  if(random == 1|| random_2 == 1 || random_3 == 1|| random_4==1 || random_5 == 1){
    gotoxy(x+ doduge_1, y - 1);
    printf(" ___ ");}

  if(random == 2|| random_2 == 2 || random_3 == 2|| random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y - 1);
    printf(" ___ ");}

  if(random == 3|| random_2 == 3 || random_3 == 3|| random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y - 1);
    printf(" ___ ");}

  if(random == 4|| random_2 == 4 || random_3 == 4|| random_4==4 || random_5 == 4){
    gotoxy(x + doduge_1, y line2doduge- 1);
    printf(" ___ ");}

  if(random == 5|| random_2 == 5 || random_3 == 5|| random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge- 1);
    printf(" ___ ");}

  if(random == 6|| random_2 == 6 || random_3 == 6|| random_4==6 || random_5 == 6){
    gotoxy(x + doduge_3, y line2doduge- 1);
    printf(" ___ ");}

  if(random == 7|| random_2 == 7 || random_3 == 7|| random_4==7 || random_5 == 7){
    gotoxy(x + doduge_1, y line3doduge- 1);
    printf(" ___ ");}

  if(random == 8|| random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8){
    gotoxy(x + doduge_2, y line3doduge- 1);
    printf(" ___ ");}

  if(random == 9|| random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9){
    gotoxy(x + doduge_3, y line3doduge- 1);
    printf(" ___ ");}

  if(random == 1|| random_2 == 1 || random_3 == 1|| random_4==1 || random_5 == 1){
    gotoxy(x+ doduge_1, y);

    printf("|");
    eye_random = 1;
    eye_1(user, eye_random);

    printf("|");}

  if(random == 2|| random_2 == 2 || random_3 == 2|| random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y);

    printf("|");
    eye_random = 2;
    eye_1(user, eye_random);

    printf("|");}

  if(random == 3|| random_2 == 3 || random_3 == 3|| random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y);

    printf("|");
    eye_random = 3;
    eye_1(user, eye_random);

    printf("|");}

  if(random == 4|| random_2 == 4 || random_3 == 4|| random_4==4 || random_5 == 4){
    gotoxy(x + doduge_1, y line2doduge);

    printf("|");
    eye_random = 4;
    eye_1(user, eye_random);

    printf("|");}

  if(random == 5|| random_2 == 5 || random_3 == 5|| random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge);

    printf("|");
    eye_random = 5;
    eye_1(user, eye_random);

    printf("|");}

  if(random == 6|| random_2 == 6 || random_3 == 6|| random_4==6 || random_5 == 6){
    gotoxy(x + doduge_3, y line2doduge);

    printf("|");
    eye_random = 6;
    eye_1(user, eye_random);

    printf("|");}

  if(random == 7|| random_2 == 7 || random_3 == 7|| random_4==7 || random_5 == 7){
    gotoxy(x + doduge_1, y line3doduge);

    printf("|");
    eye_random = 7;
    eye_1(user, eye_random);

    printf("|");}

  if(random == 8|| random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8){
    gotoxy(x + doduge_2, y line3doduge);

    printf("|");
    eye_random = 8;
    eye_1(user, eye_random);

    printf("|");}

  if(random == 9|| random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9){
    gotoxy(x + doduge_3, y line3doduge);

    printf("|");
    eye_random = 9;
    eye_1(user, eye_random);

    printf("|");}

  Sleep(100);

  if(random == 1|| random_2 == 1 || random_3 == 1|| random_4==1 || random_5 == 1){
    gotoxy(x+ doduge_1, y - 1);
    printf("      ");}

  if(random == 2|| random_2 == 2 || random_3 == 2|| random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y - 1);
    printf("      ");}

  if(random == 3|| random_2 == 3 || random_3 == 3|| random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y - 1);
    printf("      ");}

  if(random == 4|| random_2 == 4 || random_3 == 4|| random_4==4 || random_5 == 4){
    gotoxy(x + doduge_1, y line2doduge- 1);
    printf("      ");}

  if(random == 5|| random_2 == 5 || random_3 == 5|| random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge- 1);
    printf("      ");}

  if(random == 6|| random_2 == 6 || random_3 == 6|| random_4==6 || random_5 == 6){
    gotoxy(x + doduge_3, y line2doduge- 1);
    printf("      ");}

  if(random == 7|| random_2 == 7 || random_3 == 7|| random_4==7|| random_5 == 1){
    gotoxy(x + doduge_1, y line3doduge- 1);
    printf("      ");}

  if(random == 8|| random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8){
    gotoxy(x + doduge_2, y line3doduge- 1);
    printf("      ");}

  if(random == 9|| random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9){
    gotoxy(x + doduge_3, y line3doduge- 1);
    printf("      ");}

  if(random == 1|| random_2 == 1 || random_3 == 1|| random_4==1 || random_5 == 1){
    gotoxy(x+ doduge_1, y);

    printf("      ");}

  if(random == 2|| random_2 == 2 || random_3 == 2|| random_4==2 || random_5 == 2){
    gotoxy(x + doduge_2, y);

    printf("      ");}

  if(random == 3|| random_2 == 3 || random_3 == 3|| random_4==3 || random_5 == 3){
    gotoxy(x + doduge_3, y);
    printf("      ");}

  if(random == 4|| random_2 == 4 || random_3 == 4|| random_4==4 || random_5 == 4){
    gotoxy(x + doduge_1, y line2doduge);

    printf("      ");}

  if(random == 5|| random_2 == 5 || random_3 == 5|| random_4==5 || random_5 == 5){
    gotoxy(x + doduge_2, y line2doduge);

    printf("      ");}

  if(random == 6|| random_2 == 6 || random_3 == 6|| random_4==6 || random_5 == 6){
    gotoxy(x + doduge_3, y line2doduge);

    printf("      ");}

  if(random == 7|| random_2 == 7 || random_3 == 7|| random_4==7 || random_5 == 7){
    gotoxy(x + doduge_1, y line3doduge);

    printf("      ");}

  if(random == 8|| random_2 == 8 || random_3 == 8|| random_4==8 || random_5 == 8){
    gotoxy(x + doduge_2, y line3doduge);

    printf("      ");}

  if(random == 9|| random_2 == 9 || random_3 == 9|| random_4==9 || random_5 == 9){
    gotoxy(x + doduge_3, y line3doduge);

    printf("      ");}
}

void gotoxy(int x, int y)
{
  COORD Pos = { x - 1, y - 1 };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int  Input_KeyState (int user[])
{
  if (GetAsyncKeyState( VK_NUMPAD7 )&0x8001) //숫자패드 7값을 누르고
    // 이전에 누른 적이 있고 호출 시점에도 눌려있는 상태
    user[0]=1;
	
  if(GetAsyncKeyState( VK_NUMPAD8  )&0x8001)
    user[1]=2;
	
  if(GetAsyncKeyState( VK_NUMPAD9 )&0x8001)
    user[2]=3;
	
  if(GetAsyncKeyState( VK_NUMPAD4 )&0x8001)
    user[3]=4;

  if(GetAsyncKeyState( VK_NUMPAD5 )&0x8001)
    user[4]=5;
	
  if(GetAsyncKeyState( VK_NUMPAD6 )&0x8001)
    user[5]=6;
	
  if(GetAsyncKeyState( VK_NUMPAD1 )&0x8001)
    user[6]=7;
	
  if(GetAsyncKeyState( VK_NUMPAD2 )&0x8001)
    user[7]=8;

  if(GetAsyncKeyState( VK_NUMPAD3 )&0x8001)
    user[8]=9;

  return user[0], user[1], user[2], user[3], user[4], user[5], user[6], user[7], user[8];
}

void eye_1(int user[],int eye_random)
{
  Red;
  if (eye_random == user[0])
    printf("X X");
  else if (eye_random == user[1])
    printf("X X");
  else if (eye_random == user[2])
    printf("X X");
  else if (eye_random == user[3])
    printf("X X");
  else if (eye_random == user[4])
    printf("X X");
  else if (eye_random == user[5])
    printf("X X");
  else if (eye_random == user[6])
    printf("X X");
  else if (eye_random == user[7])
    printf("X X");
  else if (eye_random == user[8])
    printf("X X");
  else {
    White;
    printf("0 0");}
  White;

  score(eye_random ,user);
}

int score(int eye_random, int user[])
{
  int i=0;

  if (eye_random == user[0])
    totalscore[0] += 100;
  else if (eye_random == user[1])
    totalscore[0] += 100;
  else if (eye_random == user[2])
    totalscore[0] += 100;
  else if (eye_random == user[3])
    totalscore[0] += 100;
  else if (eye_random == user[4])
    totalscore[0] += 100;
  else if (eye_random == user[5])
    totalscore[0] += 100;
  else if (eye_random == user[6])
    totalscore[0] += 100;
  else if (eye_random == user[7])
    totalscore[0] += 100;
  else if (eye_random == user[8])
    totalscore[0] += 100;

  return totalscore[0];  //두더지 옆부분 "|" 이 위치가 바뀌므로 출력은 다른 곳에서
}

int level(int userchoice1)
{
  switch(userchoice1)
  {
    case 6:                //6을 입력받을 때 userchoice = 6.
      gotoxy(23,10);
      printf("난이도가 보통으로 설정되었습니다.");
      Sleep(1000);
      userchoice1=6;
      break;

    case 9:                //9를 입력받을 때 userchoice = 9.
      gotoxy(23,10);
      printf("난이도가 어려움으로 설정되었습니다.");
      Sleep(1000);
      userchoice1=9;
      break;

    default:             //다른 값일때 6을 입력받음.
      gotoxy(23,10);
      printf("난이도가 쉬움으로 설정되었습니다.");
      Sleep(1000);
      userchoice1=3;
      break;
  }

  system("cls");
  return userchoice1;
}

void intro_design(void)
{
  design();

  Sleep(1000);

  Yellow;
  gotoxy(32, 10);
  printf("두더지 팡팡 ~!");

  Red;
  gotoxy(39, 10);
  printf("팡\a");
  Sleep(200);
  gotoxy(39, 10);
  printf("   ");

  gotoxy(41, 10);
  printf("팡\a");
  Sleep(200);
  gotoxy(42, 10);
  printf("   ");

  Yellow;
  gotoxy(32, 10);
  printf("두더지 팡팡 ~!!!");

  gotoxy(26, 14);
  printf("시작하려면 아무키나 누르세요.");

  White;
  gotoxy(32, 18);
  printf("제작자1 : 박정훈");
  gotoxy(32, 19);
  printf("제작자2 : 박상연");
  getch();
}

void design(void)
{
  int i;

  for (i = 1; i <= 25; i++)
  {
    gotoxy(14, i);
    printf("│");
  }
  for (i = 1; i <= 25; i++)
  {
    gotoxy(64, i);
    printf("│");
  }
}

void countdown(void)
{
  //////////////////////////초반 시작 카운트다운.
  Sleep(1000);
  gotoxy(40,8);
  printf("3");
  Sleep(1000);
  gotoxy(40,8);
  printf("2");
  Sleep(1000);
  gotoxy(40,8);
  printf("1");
  Sleep(1000);
  gotoxy(38,8);
  Red;
  printf("시작!");
  Sleep(500);
  gotoxy(38,8);
  printf("        ");

  White;
}

int random_duplication_remove(int random, int random_2, int random_3,int random_4,int random_5)
{
  if(random == random_2)                        //랜덤 값의 중복을 막기 위해 사용함.
    random = 0;

  if(random == random_3)
    random = 0;

  if(random_2 == random_3)
    random_2= 0;

  if(random == random_4)
    random = 0;

  if(random == random_5)
    random = 0;

  if(random_2 == random_4)
    random = 0;

  if(random_2 == random_5)
    random = 0;

  if(random_3 == random_4)
    random = 0;

  if(random_3 == random_5)
    random = 0;

  if(random_4 == random_5)
    random_4 = 0;

  return random, random_2, random_3,random_4,random_5;
}
