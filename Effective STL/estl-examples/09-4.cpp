//
// More Examples from ESTL Item 9 
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

	{
		vector<int> c(vals1, vals1 + nvals1);
		ofstream logFile("9-4.out");				// log file to write to

		cout << "Before:" << endl;
		printContainer("vector", c);
		
		for (vector<int>::iterator i = c.begin();
				 i != c.end(); ) {
			if (badValue(*i)) {
				logFile << " Erasing " << *i << '\n';
				i = c.erase(i);						// keep i valid by assigning
			}										// erase’s return value to it
		else ++i;
		}

		printContainer("after remove, vector", c);
	}



	return 0;
}
