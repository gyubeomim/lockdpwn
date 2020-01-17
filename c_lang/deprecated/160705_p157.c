#include <stdio.h>
#include <string.h>

#define STR_LEN 50
#define BOOK_INFO_NUM 3


typedef struct __bookInfo
{
  char bookTitle[STR_LEN];
  char bookPub[STR_LEN];
  int bookPrice;
} bookInfo;


int numOfData = 0;
bookInfo bookInfoList[BOOK_INFO_NUM];

/* p164 다양한 정렬기준 추가 */
enum{SORT_TITLE=1, SORT_PUB, SORT_PRICE, EXIT};
bookInfo * bookSortList[BOOK_INFO_NUM];


int InsertList(bookInfo *bookPtr);

/* p164 다양한 정렬기준 추가 */
void InitSortList();
void PrintSortList();

void SortByTitle();
void SortByPubName();
void SortByPrice();


void main()
{
  int i,num;
  bookInfo book;

  for(i=0; i < BOOK_INFO_NUM ; i++)
  { 
    printf("****************************\n");
    printf("%d번째 도서정보 입력\n",i+1);

    printf("도서 제목 : ");
    gets(book.bookTitle);
    
    printf("출판사 명 : ");
    gets(book.bookPub);

    printf("도서 가격 : ");
    scanf("%d",&book.bookPrice);

    num = InsertList(&book); // 새로운 함수... 지만 아직도 루프에서 에러난다 ㅠㅠ

    if(num==-1)
    {
      printf("입력이 실패했습니다 \n");
    }
    else
    {
      printf("%d번째 입력 완료\n\n",i+1);
    }
    
    
  }
  
  puts("***************** 도서 정보 출력 ***************");
  for(i=0; i<BOOK_INFO_NUM;i++)
  {
    printf("%d번째 도서 정보 출력 \n",i+1);
    printf("도서 제목 : %s\n",bookInfoList[i].bookTitle);
    printf("출판사 명 : %s\n",bookInfoList[i].bookPrice);
  }
  
}


int InsertList(bookInfo *bookPtr)
{
  int idx;
  int inputIdx = numOfData;

  if(numOfData >= BOOK_INFO_NUM)
    return -1;

  /* 입력 위치 찾기 */
  for(idx=0; idx< numOfData; idx++)
  {
    if(strcmp(bookInfoList[idx].bookTitle,bookPtr->bookTitle)>0)
    {
      inputIdx = idx;
      break;
    }
  }

  /* 입력이 가능하도록 자리를 마련한다 */
  for(idx=numOfData; idx>inputIdx; idx--)
  {
    bookInfoList[idx] = bookInfoList[idx-1];
  }

  /* 새로운 데이터를 입력한다 */
  bookInfoList[inputIdx] = (*bookPtr);


  return ++numOfData;

  
}
