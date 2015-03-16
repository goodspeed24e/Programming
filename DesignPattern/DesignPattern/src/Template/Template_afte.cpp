
#include <iostream>
using namespace std;

class Template_Base {
	void a() { cout << "a   "; }
	void b() { cout << "b   "; }
	void c() { cout << "c   "; }
	// 2. steps requiring peculiar implementations
	// are "placeholders" in base class
	virtual void ph1() = 0;
	virtual void ph2() = 0;
public:
	// 1. standardize the skeleton of an alogrithm 
	// in a base class
	void execute() { a(); ph1(); b(); ph2(); c(); }
};

class Template_One: public Template_Base {
	// 3. Derived classes implementation placeholder methods
	void ph1() { cout << "b   "; }
	void ph2() { cout << "d   "; }
};

class Template_Two: public Template_Base
{
	void ph1() { cout << "2   "; }
	void ph2() { cout << "4   "; }
};

/**
 * \brief
 *  Template Method design pattern
 * 
 * 1. Standardize the skeleton of an algorithm in a base class "template method"
 * 2. Steps requiring peculiar implementations are "placeholders" in base class
 * 3. Derived classes implement placeholder methods
*/
void main( void )
{
	Template_Base * arr[] = { &Template_One(), &Template_Two() };
	for ( int i = 0 ; i < 2; i++ ){
		arr[i]->execute();
		cout << "\n";
	}
}