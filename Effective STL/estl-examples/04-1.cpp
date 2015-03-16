//
// Example from ESTL Item 4
//

#include <list>
#include <iostream>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	const int vals1[] = { 1, 2, 3, 4, 5};

	const int nvals1 = sizeof vals1 / sizeof(int);

	const int vals2[] = { -3, 2, 5, 6, 9, 102, -15, 10 , 11, 12};
	const int nvals2 = sizeof vals2 / sizeof(int);

	list<int> list1(vals1, vals1 + nvals1);
	list<int> list2(vals2, vals2 + nvals2);
	
	cout << "Before:" << endl;
	printContainers("list1", list1, "list2", list2);

	list1.splice(									// move all nodes in list2
	  list1.end(), list2,							// (from the first occurrence
	  find(list2.begin(), list2.end(), 5),			// of 5 up to — but not
	  find(list2.rbegin(), list2.rend(), 10).base()	// including — the last
	);												// occurrence of 10) to the
													// end of list1. See Item 28
	cout << "After:" << endl;
	printContainers("list1", list1, "list2", list2);
													// for info on the “base()” call
	return 0;
}
