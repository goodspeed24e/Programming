
/*
Bridge design pattern demo

The motivation is to decouple the time interface from the Time implemenations, while still allowing the 
abstraction and the realization to each be modelled with their own inheritance hierarchy. 
The implemenation class below are straight-forward, the interface classes are a little more subtle. 
Routinely, a Bridge pattern interface hierarchy "hasa" implementation class. here the interface base class
 "hasa" pointer to the implementation base class, and each class pointer with the correct concrete implementation
 class. then all requests from the client are simply delegated by the interface class to the cnapsulated implementation class

*/
#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

class TimeImp{
public:
	TimeImp(int hr, int min){
		hr_ = hr, min_ = min;
	}
	virtual void output(){
		cout << "time is " << setw(2) << setfill('0') << hr_ << min_ << endl;
	}
protected:
	int hr_, min_;
};

class CivilianTimeImp: public TimeImp{
public:
	CivilianTimeImp(int hr, int min, int pm): TimeImp(hr, min){
	if (pm)
		strcpy(whichM_, " PM");
	else
		strcpy(whichM_, " AM");
	}
	void output(){
		cout << "time is " << hr_ << ":" << min_ << whichM_ << endl;
	}
protected:
	char whichM_[4];
};

class ZuluTimeImp: public TimeImp{
public:
	ZuluTimeImp(int hr, int min, int zone): TimeImp(hr, min){
	if (zone ==5)
		strcpy(zone_, " Eastern Standard Time");
	else if (zone == 6)
		strcpy(zone_, " Central Standard Time");
	}
	void output(){
		cout << "time is " << setw(2) << setfill('0') << hr_ << min_ << zone_ << endl;
	}
protected:
	char zone_[32];
};

class Time{
public:
	Time(){}
	Time( int hr, int min ){
		imp_ = new TimeImp( hr, min );
	}
	virtual void output(){
		imp_->output();
	}
protected:
	TimeImp* imp_;
};

class CivilianTime: public Time{
public:
	CivilianTime( int hr, int min, int pm){
		imp_ = new CivilianTimeImp( hr, min, pm );
	}
};

class ZuluTime: public Time{
public:
	ZuluTime( int hr, int min, int zone){
		imp_ = new ZuluTimeImp( hr, min, zone);
	}
};

void main( void){
	Time* times[3];
	times[0] = new Time(4,30);
	times[1] = new CivilianTime(2, 30, 1);
	times[2] = new ZuluTime ( 14, 30, 6 );
	for (int i = 0; i < 3; i++)
	times[i]->output();
}