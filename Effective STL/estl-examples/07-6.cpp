//
// Sixth example from Item 7 (using Boost shared pointers)
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"
#include "Widget.h"
#include <boost/smart_ptr.hpp>		// from Boost

using namespace std;
using namespace ESTLUtils;

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);
const int SOME_MAGIC_NUMBER = 10;


void doSomething()
{
	typedef boost::shared_ptr<Widget> SPW;			// SPW = “	shared_ptr
													// 	to Widget” 
	vector<SPW> vwp;
	for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
		vwp.push_back(SPW(new Widget)); 			// create SPW from a
													// Widget*, then do a
													// push_back on it
													// use vwp
}					// no Widgets are leaked here, not
					// even if an exception is thrown
					// in the code above

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	doSomething();

	return 0;
}
