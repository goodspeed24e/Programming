//
// Example from Item 32
//

#include <iostream>
#include <vector>
#include <list>

#include "ESTLUtil.h"

int data[] = { -30, 102, 99, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<int> v;							// create a vector<int> and fill it with
	v.reserve(10);							// the values 1-10. (See Item 14 for an
	for (int i = 1; i <= 10; ++i) {			// explanation of the reserve call.)
		v.push_back(i);
	}

	cout << v.size() << endl;				// prints 10

	v[3] = v[5] = v[9] = 99;				// set 3 elements to 99

	printContainer("Before remove, v", v);

//	remove(v.begin(), v.end(), 99);			// remove all elements with value 99

//	vector<int>::iterator newEnd(remove(v.begin(), v.end(), 99));

	v.erase(remove(v.begin(), v.end(), 99), v.end());	// really remove all
														// elements with value 99
	printContainer("After remove,  v", v);
	cout << v.size() << endl;					// now returns 7


	list<int> li(data, data+numValues);		// create a list

	printContainer("Before remove, li", li);
	

	li.remove(99);		// eliminate all elements with value 99;
						// this really removes elements, so li's
						// size may change!

	printContainer("After remove, li", li);

	return 0;

}
