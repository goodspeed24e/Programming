// Inheritance run amok

#include <iostream>
using namespace std;


class A{
public:
	virtual void doIt() { cout << "A"; }
};

class AwithX: public A{
public:
	void doIt(){
		A::doIt();
		do_X();
	}
private:
	void do_X() { cout << "X"; }
};

class AwithY: public A{
public:
	void doIt(){
		A::doIt();
		do_Y();
	}
protected:
	void do_Y() { cout << "Y"; }
};

class AwithZ: public A{
public:
	void doIt(){
		A::doIt();
		do_Z();
	}
protected:
	void do_Z() { cout << "X"; }
};

class AwithXY: public AwithX, public AwithY{
public:
	void doIt(){
		AwithX::doIt();
		AwithY::do_Y();
	}
};

class AwithXYZ: public AwithX, public AwithY, public AwithZ{
public:
	void doIt(){
		AwithX::doIt();
		AwithY::do_Y();
		AwithZ::do_Z();
	}
};

int main(void)
{
	AwithX		anX;
	AwithY		anY;
	AwithZ		anZ;
	anX.doIt();	cout << endl;
	anY.doIt();	cout << endl;
	anZ.doIt();	cout << endl;
}