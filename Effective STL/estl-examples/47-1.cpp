//
// Example from Item 47
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"

int data[] = { 30, 102, 55, 19, 0, 222, 3000, 4000, 8, 2 };
const int numValues = sizeof data / sizeof(int);

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<int> v;
	v.insert(v.begin(), data, data + numValues);	// insert the ints in data
													// into v at the front
	printContainer("after initialization, v", v);
	vector<int> v_save = v;
	
	int x = 100, y =2500;		// remove elements < 100 except those preceding
								// the last element >= 2500

	{
		v.erase(
			remove_if(find_if(v.rbegin(), v.rend(), 
							  bind2nd(greater_equal<int>(), y)).base(),
					  v.end(), 
					  bind2nd(less<int>(), x)),
			v.end());

		printContainer("after erasing, v", v);
	}

	{
		v = v_save;
		printContainer("after re-initialization, v", v);

		typedef vector<int>::iterator VecIntIter;

		// initialize rangeBegin to point to the element following the last
		// occurrence of a value greater than or equal to y. If there is no such
		// value, initialize rangeBegin to v.begin(). If the last occurrence of the
		// value is the last element in v, initialize rangeBegin to v.end()
		VecIntIter rangeBegin =
			find_if(v.rbegin(), v.rend(), 
					bind2nd(greater_equal<int>(), y)).base();

		// from rangeBegin to v.end(), erase everything with a value less than x
		v.erase(remove_if(rangeBegin, v.end(), bind2nd(less<int>(), x)), v.end());

		printContainer("after 2nd erasure, v", v);
	}
	return 0;
}
