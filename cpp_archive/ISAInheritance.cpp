/*
	열혈 c++ IS A 로 이뤄진 상속의 관계를 설명한 코드 
	~는 ~의 일종이다
*/
#include "stdafx.h"
#include <iostream>



using namespace std;



class Computer
{
private:
	char owner[50];

public:
	Computer(char *name)
	{
		strcpy_s(owner,100,name);
	}

	void Calculate()
	{
		cout << "요청 내용을 계산합니다" << endl;
	}

};


class NotebookComp : public Computer
{
private:
	int Battery;

public:
	NotebookComp(char *name, int initChag)
		: Computer(name), Battery(initChag)
	{}

	void Charging() { Battery += 5; }
	
	
	void UseBattery() { Battery -= 1; }
	


	int GetBatteryInfo() { return Battery; }


	void MovingCal()
	{
		if (GetBatteryInfo() < 1)
		{
			cout << "충전이 필요합니다" << endl;
		}

		cout << "이동하면서 ";
		Calculate();
		UseBattery();
	}



};


class TableNoteBook : public NotebookComp
{

private:
	char regstPenModel[50];

public:
	TableNoteBook(char *name, int initChag, char *pen)
		:NotebookComp(name, initChag)
	{
		strcpy_s(regstPenModel, 100, pen);
	}


	void Write(char *penInfo)
	{
		if (GetBatteryInfo() < 1)
		{
			cout << "충전이 필요합니다" << endl;
			return;
		}

		if (strcmp(regstPenModel, penInfo) != 0)
		{
			cout << "등록된 펜이 아닙니다";
			return;
		}
		
		cout << "필기 내용을 처리합니다" << endl;
		UseBattery(); 

	}




};



int main()
{
	NotebookComp nc("임규범", 5);
	TableNoteBook tn("edward", 5, "hello");
	nc.MovingCal();
	tn.Write("hello");

	return 0;


}






