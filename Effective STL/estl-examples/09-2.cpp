//
// More Example from ESTL Item 9 (the "remove_if" variations)
//
// Fails to compile under MSVC/native lib (library problem?)
//

#include <list>
#include <vector>
#include <set>
#include <iostream>
#include "ESTLUtil.h"

bool badValue(int x)								// returns whether x is "bad"
{
	return (x > 2 && x < 5);
}

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	const int vals1[] = { 1, 1963, 2, 3, 4, 1963, 5};

	const int nvals1 = sizeof vals1 / sizeof(int);

	{
		vector<int> c(vals1, vals1 + nvals1);

		cout << "Before:" << endl;
		printContainer("vector", c);
		
		c.erase( remove_if(c.begin(), c.end(), badValue),	// this is the best way to
						c.end());							// get rid of objects
															// where badValue
															// returns true when c is
															// a vector, string, or
															// deque
		printContainer("after remove, vector", c);
	}

	{
		list<int> l(vals1, vals1 + nvals1);

		cout << "Before:" << endl;
		printContainer("l", l);
		
		l.remove_if(badValue);						// this is the best way to get rid of
													// objects where badValue returns
													// true when c is a list

		printContainer("after remove, l", l);
	}

	{
		set<int> c(vals1, vals1 + nvals1);

		cout << "Before:" << endl;
		printContainer("set", c);
		
		set<int> goodValues;					// temporary container
												// to hold unremoved
												// values
		remove_copy_if(c.begin(), c.end(),		// copy unremoved
				inserter( goodValues,			// values from c to
						  goodValues.end()),	// goodValues
				badValue);
		c.swap(goodValues);						// swap the contents of
												// c and goodValues

		printContainer("after erase, set", c);
	}
	return 0;
}
