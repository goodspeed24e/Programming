//
// Examples from Introduction
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"


template<typename C>
bool lastGreaterThanFirst(const C& container)
{
	if (container.empty()) return false;
	typename C::const_iterator begin(container.begin());
	typename C::const_iterator end(container.end());
	return *--end > *begin;
}

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	const int ints[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
	const size_t nints = sizeof ints / sizeof (int);

	vector<int> v(ints, ints + nints);
	printContainer("v", v);

	cout << "lastGreaterThanFirst(v) returns: " <<
				lastGreaterThanFirst(v) << endl;

	v[0] = 5;

	cout << "lastGreaterThanFirst(v) returns: " <<
				lastGreaterThanFirst(v) << endl;

	return 0;
}
