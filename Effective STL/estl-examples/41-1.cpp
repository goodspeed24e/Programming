//
// Example from ESTL Item 41
//

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "ESTLUtil.h"
#include "Widget.h"
using namespace std;

/*class Widget {
public:
//	...
	Widget(int n) {}
	void test();				// perform a self-test; mark *this
//	...							// as "failed" if it doesn't pass
};
*/

class T
{
public:
	void f() {}
};

void f(T x)
{}

int test(Widget& w)					// test w and mark it as "failed" if
{									// it doesn't pass the test
	cout << "Testing Widget(" << w.getVal() << ")" << endl;
	return 0;
}

/* Just an "envision statement"...
template<typename InputIterator, typename Function>
Function for_each(InputIterator begin, InputIterator end, Function f)
{
	while (begin != end) f(*begin++);
}
*/

/*
template<typename R, typename C>	// declaration for mem_fun for 
mem_fun_t<R,C>						// non-const member functions
mem_fun(R (C::*pmf)());				// taking no parameters. C is the
									// class, R is the return type of the
									// pointed-to member function
*/

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	T x, *pt = &x;

	f(x);
	x.f();
	pt->f();
	
	///////////////////////////////////
	vector<Widget> vw;					// vw holds widgets
	vw.push_back(Widget(1));
	vw.push_back(Widget(2));
	vw.push_back(Widget(3));
	vw.push_back(Widget(4));

	for_each(vw.begin(), vw.end(), test);			// Call #1 (compiles)

//	for_each(vw.begin(), vw.end(),
//			&Widget::test);							// Call #2 (won't compile)

	list<Widget*> lpw;								// lpw holds pointers to widgets
	lpw.push_back(new Widget(1));
	lpw.push_back(new Widget(2));
	lpw.push_back(new Widget(3));
	lpw.push_back(new Widget(4));

//	for_each(lpw.begin(), lpw.end(),
//		&Widget::test);								// Call #3 (also won't compile)


	for_each(lpw.begin(), lpw.end(),
			mem_fun(&Widget::test));				// this will now compile

	for_each(vw.begin(), vw.end(), test);			// as above, Call #1;
							// this compiles


/*
	for_each(vw.begin(), vw.end(), &Widget::test);		// as above, Call #2;
														// doesn't compile

	for_each(lpw.begin(), lpw.end(), &Widget::test);	// as above, Call #3;
														// doesn't compile
*/

	for_each(vw.begin(), vw.end(), ptr_fun(test));		// compiles and behaves
														// like Call #1 above

	return 0;
}
