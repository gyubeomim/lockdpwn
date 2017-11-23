#ifndef __PERSON_H__
#define __PERSON_H__

#define STR_LEN    50

typedef struct _person
{
	int ssn;				// 주민등록번호 
	char name[STR_LEN];		// 이름
	char addr[STR_LEN];		// 주소
} Person;

int GetSSN(Person * p);
void ShowPerInfo(Person * p);
Person * MakePersonData(int ssn, char * name, char * addr);

#endif