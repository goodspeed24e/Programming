//
// Example from Item 33
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"
#include "Widget.h"
#include "smart_ptr.h"
using namespace std;
using namespace ESTLUtils;

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);
const int SOME_MAGIC_NUMBER = 10;

void delAndNullifyUncertified(Widget*& pWidget) 	// if *pWidget is an
{													// uncertified Widget,
	if (!pWidget->isCertified()) {					// delete the pointer
		delete pWidget;								// and set it to null
		pWidget = 0;
	}
}

int main()
{
	using namespace std;
	using namespace ESTLUtils;
	using namespace boost;

	vector<Widget*> v;					// create a vector and fill it with
										// pointers to dynamically 
	v.push_back(new Widget);			// allocated Widgets
	v.push_back(new Widget(10));
	v.push_back(new Widget(9));
	v.push_back(new Widget(99));
	v.push_back(new Widget(102));
	
	printContainer("v before erase", v);


/*
	v.erase(remove_if(	v.begin(), v.end(),		// erase the pointers to
		not1(mem_fun(&Widget::isCertified))),	// uncertified Widgets;
		v.end());								// see Item 41 for info
*/
	for_each(v.begin(), v.end(),					// delete and set to
		delAndNullifyUncertified);					// null all ptrs to 
													// uncertified widgets

	v.erase(remove(v.begin(), v.end(), static_cast<Widget *>(0)), v.end());	// eliminate all null
													// ptrs from v


	printContainer("v after erase", v);

	//////////////////////////////////////////////////////////////////////

#define RCSP shared_ptr
	
	{
	typedef RCSP<Widget> RCSPW;		// RCSPW = “RCSP to Widget”
	vector<RCSP<Widget> > v;		// create a vector and fill it with
									// smart pointers to dynamically 
	v.push_back(RCSPW(new Widget()));		// allocated Widgets
	v.push_back(RCSPW(new Widget(10)));
	v.push_back(RCSPW(new Widget(9)));
	v.push_back(RCSPW(new Widget(99)));
	v.push_back(RCSPW(new Widget(102)));

	printContainer("v before erase", v);

	v.erase(remove_if(v.begin(), v.end(),		// erase the ptrs
		not1(mem_fun(&Widget::isCertified))),	// to uncertified 
		v.end());								// Widgets; no
												// resources are
												// leaked
	printContainer("v after erase", v);

	}
	return 0;
}
