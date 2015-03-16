// Make the class responsible for its own global pointer
// and 'initialization on first use' ( by using a private static
// pointer and a public static accessor method). 
// the client uses only the public accessor method.

#include <iostream>
using namespace std;

class GlobalClass{
private:
	int				m_value;
	static	GlobalClass* s_inst;
	GlobalClass( int v=0)	{ m_value = v;}
public:
	int	getVal()					{ return m_value; }
	void setVal(int v)				{ m_value = v; }
	static GlobalClass* instance(){
		if (!s_inst)
			s_inst = new GlobalClass;
		return s_inst;
	}
};

// Allocating and initailizing GlobalClass's static data member,
// the pointer is being allocated - not the object itself
GlobalClass* GlobalClass::s_inst = 0;

void foo(void){
	GlobalClass::instance()->setVal( 1 );
	cout << "foo: global_ptr is " << GlobalClass::instance()->getVal() << endl;
}

void bar(void){
	GlobalClass::instance()->setVal(2);
	cout << "bar: global_ptr is" << GlobalClass::instance()->getVal()<< endl;
}

void main( void )
{
	cout << "main:global_ptr is" << GlobalClass::instance()->getVal() << endl;
	foo();
	bar();
}
