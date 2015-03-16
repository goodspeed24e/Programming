//
// Example from ESTL Item 44
//

#include <string>
#include <set>
#include <iostream>
#include "ESTLUtil.h"


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	set<int> s;				// create set, put
							// 1,000,000 values
							// into it

	for (size_t j = 0; j < 1000000; j++)
		s.insert(j);

	set<int>::iterator i = s.find(727);			// use find member
	if (i != s.end())							// function
		cout << "Found 727 in set with member find." << endl;

	{
	set<int>::iterator i = find(s.begin(), s.end(), 727);	// use find algorithm
	if (i != s.end())
		cout << "Found 727 in set with algorithm find." << endl;
	}

	return 0;
}
