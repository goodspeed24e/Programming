
#include <iostream>
using namespace std;
// Replacing inheritance with wrapping-delegation
// Use aggregation instead of inheritance to implement embellishments to 
// a "core" object. Client can dynamically compose permutations, instead of the architect
// statically wielding multiple inheritance

class I{
public:
	virtual ~I(){}; // interface
	virtual void doIt() = 0;
};

class A: public I{
public:
	~A(){ cout << "A dtor" << endl;}
	void doIt() { cout << "A";}
};

class D: public I{
public:
	D (I* inner)			{ m_wrappee =inner;}
	~D()						{ delete m_wrappee;}
	void doIt()			{ m_wrappee->doIt();}
private:
	I* m_wrappee;
};

class X: public D{
public:
	X( I* core):D(core){};
	~X() { cout << "X dtor" << "      ";}
	void doIt(){
		D::doIt();
		cout << "-X";
	}
};

class Y: public D{
public:
	Y( I* core):D(core){};
	~Y() { cout << "Y dtor" << "      ";}
	void doIt(){
		D::doIt();
		cout << "-Y";
	}
};

class Z: public D{
public:
	Z( I* core):D(core){};
	~Z() { cout << "Z dtor" << "      ";}
	void doIt(){
		D::doIt();
		cout << "-Z";
	}
};

int main(void)
{
	I* anX			=	new X( new A);
	I* anXY		=	new Y( new X ( new A));
	I* anXYZ		=	new Z( new Y ( new X ( new A)));
	anX->doIt();			cout << endl;
	anXY->doIt();		cout << endl;
	anXYZ->doIt();		cout << endl;
	delete anX; delete anXY; delete anXYZ;

	I* anZXY		= new Z( new X( new Y ( new A)));
	anZXY->doIt();		cout << endl;
	delete anZXY;
}