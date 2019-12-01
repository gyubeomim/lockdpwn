#include <stdio.h>

#define STR_LEN 50
#define BOOK_INFO_NUM 3

typedef struct __bookInfo
{
  char bookTitle[STR_LEN];
  char bookPub[STR_LEN];
  int bookPrice;
} bookInfo;

bookInfo bookInfoList[BOOK_INFO_NUM];

void main()
{
  int i;

  for(i=0; i<BOOK_INFO_NUM ; i++)
  { 
    printf("****************************\n");
    printf("%d번째 도서정보 입력\n",i+1);

    // 왜그런지 모르겠는데 두번째 루프부터 에러가 난다
    printf("도서 제목 : ");
    gets(bookInfoList[i].bookTitle);
    
    printf("출판사 명 : ");
    gets(bookInfoList[i].bookPub);

    printf("도서 가격 : ");
    scanf("%d",&bookInfoList[i].bookPrice);

    
    //fflush(stdin);  // 이건 왜 넣는거지..?
     
    printf("%d번째 입력 완료\n",i+1);

  }

  puts("***************** 도서 정보 출력 ***************");
  for(i=0; i<BOOK_INFO_NUM;i++)
  {
    printf("%d번째 도서 정보 출력 \n",(i+1));
    printf("도서 제목 : %s\n",bookInfoList[i].bookTitle);
    printf("출판사 명 : %s\n",bookInfoList[i].bookPub);
    printf("도서 가격 : %d\n",bookInfoList[i].bookPrice);
  }
  
}
