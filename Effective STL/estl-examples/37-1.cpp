//
// Example from ESTL Item 37
//

#include <list>
#include <iostream>
#include <numeric>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	const int vals[] = { 1, 2, 3, 4, 5};
	const int nvals = sizeof vals / sizeof(int);


	list<double> ld;			// create a list and put
								// some doubles into it

	for (int j = 0; j < nvals; j++)
		ld.push_back(vals[j] * .3);

	double sum = accumulate(ld.begin(), ld.end(), 0.0);	// calculate their sum, 
														// starting at 0

	show(ld);
	cout << "sum = " << sum << endl;

	return 0;
}
