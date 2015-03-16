//
// Example from Item 34
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"

int data[] = { -30, 102, 55, 5, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<int> v;					// create a vector, put some
									// data into it, sort it into
									// descending order
	v.insert(v.begin(), data, data + numValues);
	sort(v.begin(), v.end(), greater<int>());
	printContainer("after sort, v", v);

	//...							// work with the vector
									// (without changing it)

	{
	bool a5Exists =								// search for a 5 in the vector,
		binary_search(v.begin(), v.end(), 5);	// assuming it's sorted in
											    // ascending order!
	cout << "First time, a5Exists = " << a5Exists << endl;
	}	

	{
	bool a5Exists =												// search for a 5 
		binary_search(v.begin(), v.end(), 5, greater<int>());	// using greater as
																// the comparison
																// function
	cout << "Second time, a5Exists = " << a5Exists << endl;
	}


	
	return 0;
}
