//
// More Examples from ESTL Item 9 (the associative container variations)
//

#include <list>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
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

/*
	{
		set<int> c(vals1, vals1 + nvals1);

		cout << "Before:" << endl;
		printContainer("set", c);
		
		for (set<int>::iterator i = c.begin();		// clear, straightforward,
			 i != c.end();							// and buggy code to
			 ++i) {									// erase every element
			if (badValue(*i)) c.erase(i);			// in c where badValue
		}											// returns true; don’t
													// do this!
		printContainer("after erase, set", c);
	}
*/
	
	{
		set<int> c(vals1, vals1 + nvals1);

		cout << "Before:" << endl;
		printContainer("set", c);
		
		for (set<int>::iterator i = c.begin();		// the 3rd part of the for
			 i != c.end();							// loop is empty; i is now
			 /* nothing */ ) {						// incremented below
			
		if (badValue(*i)) c.erase(i++);				// for bad values, pass the
			else ++i;								// current i to erase and
		}											// increment i as a side

		printContainer("after erase, set", c);
	}


	{
		set<int> c(vals1, vals1 + nvals1);

		cout << "Before:" << endl;
		printContainer("set", c);
		
		ofstream logFile("9-3.out");					// log file to write to

		for (set<int>::iterator i = c.begin();			// loop conditions are the
			 i != c.end(); ) {							// same as before
			if (badValue(*i)) {
				logFile << " Erasing " << *i << '\n';	// write log file
				c.erase(i++);							// erase element
			}
			else ++i;
		}
		
		printContainer("after erase, set", c);
	}
	
	return 0;
}

