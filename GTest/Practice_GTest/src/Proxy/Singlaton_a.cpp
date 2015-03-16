
#include <iostream>

using namespace std;

class GlobalClass{
private:
	int value;
	static GlobalClass* inst;
	GlobalClass( int v = 0 ) { value = v;}
public:
	int	getValue()			{ return value;}
	void setValue(int v)		{ value = v; }
	static GlobalClass* instance(){
		if (! inst )
			inst = new GlobalClass;
		return inst;
	}
};

// Allocating and initializing GlobalClass's
// static data member. The pointer is being allocated - not the object inself.
GlobalClass* GlobalClass::inst= 0;

void foo( void ){
	GlobalClass::instance()->setValue(1);
	cout << "foo: global ptr is" << GlobalClass::instance()->getValue() << endl;
}

void bar( void ){
	GlobalClass::instance()->setValue(2);
	cout << "bar: global ptr is" << GlobalClass::instance()->getValue() << endl;
}

int main( void ){
	cout << "main: global ptr is" << GlobalClass::instance()->getValue() << endl;
	foo();
	bar();
}