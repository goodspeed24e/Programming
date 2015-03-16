
// Bridge
/*
 Even though Date has a clean interface and a well encapsulated 
 implementation, the client still has to recompiler if the class architect
 changes his/her mind.
 Instead, create a wrapper ( or interface) class that contains and deletgates
 to a body ( or implemenation) class. Client can now specify at run-time exactly what
 s/he wants.
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

class DateImp;

class Date{
public:
	Date( int y, int m, int d );
	~Date();
    void output();
	static void setImp( char* t){
		strcpy( impType_, t);
	}
private:
	DateImp* rep_;
	static char impType_[10];
};

char Date::impType_[] = "Ok";

class DateImp{
public:
	virtual void output() = 0;
};

class DateOk:public DateImp{
public:
	DateOk(int y, int m, int d);
	void output();
private:
	int year_, month_, day_;
};

class DateAA:public DateImp{
public:
	DateAA(int y, int m, int d);
    void output();
private:
	int			toJulian( int, int, int);
	char*		fromJulian(void);
	int			julian_;
	int			year_;
	static int DateTable_[2][13];
};

Date::Date(int y, int m, int d)
{
	if (!strcmp(impType_, "Ok"))
		rep_ = new DateOk(y,m,d);
	else
		rep_ = new DateAA(y,m,d);
};
Date::~Date() { delete  rep_;}
void Date::output() { rep_->output(); }

//#include "bridge2.inc"

void main( void )
{
	Date d1(1996,2,29);
	Date d2(1996,2,30);
	Date::setImp("AA");
	Date d3(1996,2,29);
	Date d4(1996,2,30);

	d1.output(); d2.output();
	cout << endl;
	d3.output(); d4.output();
	cout << endl;
}