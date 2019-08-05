#ifndef __NAME_CARD_H__
#define __NAME_CARD_H__

#define NAME_LEN		30
#define PHONE_LEN		30

typedef struct __namecard
{
	char name[NAME_LEN];
	char phone[PHONE_LEN];
} NameCard;


// NameCard 구조체 변수의 동적 할당 및 초기화 후 주소 값 반환
NameCard * MakeNameCard(char * name, char * phone);
   
// NameCard 구조체 변수의 정보 출력
void ShowNameCardInfo(NameCard * pcard);
   
// 이름이 같으면 0, 다르면 0이 아닌 값 반환
int NameCompare(NameCard * pcard, char * name);
   
// 전화번호 정보를 변경
void ChangePhoneNum(NameCard * pcard, char * phone);


#endif