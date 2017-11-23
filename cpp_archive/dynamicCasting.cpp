#include <iostream>


using namespace std;

// 기초클래스
class Car
{
private:
	int fuelGauge;

public:
	Car(int fuel) : fuelGauge(fuel)
	{}

	void showCarStatus()
	{
		cout << "fuel : " << fuelGauge << endl;
	}

};



// 유도클래스
class Truck : public Car
{
private:
	int frieghtWeight;

public:
	Truck(int fuel, int weight) : Car(fuel), frieghtWeight(weight)
	{}


	void showTruckStatus()
	{
		cout << "Weight : " << frieghtWeight << endl;
	}


};


// dynamic_cast의 의미 : 상속관계에 있는 유도클래스의 포인터 및 참조형 데이터를 기초 클래스의 포인터 및 참조형 데이터로 형 변환하겠습니다!
int main()
{
	Car* pcar1 = new Truck(80, 200);
	//	Truck* ptruck1 = dynamic_cast<Truck*>(pcar1);

	Car* pcar2 = new Car(120);
	//	Truck* ptruck2 = dynamic_cast<Truck*>(pcar2);


	Truck* ptruck3 = new Truck(70, 150);
	Car* pcar3 = dynamic_cast<Car*>(ptruck3);


	ptruck3->showCarStatus();
	ptruck3->showTruckStatus();

	cout << "----------------------------------" << endl;
	pcar3->showCarStatus();

	return 0;
}