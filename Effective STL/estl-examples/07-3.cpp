//
// Third example from Item 7 ("delete" as a function object):
//
// Fails under MSVC (any lib)
//


#include <iostream>
#include <vector>

#include "ESTLUtil.h"
#include "Widget.h"

using namespace std;
using namespace ESTLUtils;

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);
const int SOME_MAGIC_NUMBER = 10;

template<typename T>
struct DeleteObject:								// Item 40 describes why
			public unary_function<const T*, void> { // this inheritance is here
	void operator()(const T* ptr) const
// This line draws an error from MSVC:
	{ delete ptr; }
};

void doSomething()
{
	vector<Widget*> vwp;
	for (int j = 0; j < SOME_MAGIC_NUMBER; ++j)
		vwp.push_back(new Widget(j));
						// use vwp

	for_each(vwp.begin(), vwp.end(), DeleteObject<Widget>());
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	doSomething();

	return 0;
}
