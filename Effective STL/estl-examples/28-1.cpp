//
// Example from Item 28
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<int> v;
	v.reserve(5); // see Item 14
	for (int j = 1; j <= 5; ++j) {			// put 1-5 in the vector
		v.push_back(j );
	}

	printContainer("v", v);

	vector<int>:: reverse_iterator ri =		// make ri point to the 3
			find(v.rbegin(), v.rend(), 3);
	vector<int>::iterator i(ri.base());		// make i the same as ri’s base

	cout << "After finding the 3, *i = " << *i << ", *ri = " << *ri << endl;


/*
	v.erase(--ri.base());					// attempt to erase at the position
											// preceding ri.base(); for a vector,
											// this will typically not compile
											// (With VC++, compiles w/Dinkumware
											// library, but not the stock library)
*/

	v.erase((++ri).base());					// erase the element pointed to
											// ri; this should always compile
	printContainer("v", v);

	return 0;
}
