//
// Another example from ESTL Item 50
//

#include <string>
#include <iostream>
#include <vector>
#include "ESTLUtil.h"

int transmogrify(int x);				// this function produces
										// some new value from x

int transmogrify(int x)
{
	return x + 10;
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<int> values;

	values.push_back(1);
	values.push_back(10);
	values.push_back(100);
	values.push_back(37);
	

	vector<int> results;
	transform(values.begin(), values.end(), 	// this will attempt to
				results.end(),					// write beyond the 
				transmogrify);					// end of results!

	return 0;
}
