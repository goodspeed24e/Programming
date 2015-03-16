//
// Example from ESTL Item 9
//

#include <list>
#include <vector>
#include <set>
#include <iostream>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	const int vals1[] = { 1, 1963, 2, 3, 4, 1963, 5};

	const int nvals1 = sizeof vals1 / sizeof(int);

	{
		vector<int> v(vals1, vals1 + nvals1);

		cout << "Before:" << endl;
		printContainer("v", v);
		
		v.erase( remove(v.begin(), v.end(), 1963),	// the erase-remove idiom is
							v.end());				// the best way to get rid of
													// elements with a specific
													// value when c is a vector,
		printContainer("after remove, v", v);		// string, or deque	
	}

	{
		list<int> l(vals1, vals1 + nvals1);

		cout << "Before:" << endl;
		printContainer("l", l);
		
		l.remove(1963);								// the remove member function is the
													// best way to get rid of elements with
													// a specific value when c is a list
		printContainer("after remove, l", l);
	}

	{
		set<int> s(vals1, vals1 + nvals1);

		cout << "Before:" << endl;
		printContainer("s", s);
		
		s.erase(1963);								// the remove member function is the
													// best way to get rid of elements with
													// a specific value when c is a list
		printContainer("after erase, s", s);
	}
	return 0;
}
