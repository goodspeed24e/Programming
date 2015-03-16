//
// Examples from Item 23
//

#include <iostream>
#include <vector>
#include "Widget.h"

#include "ESTLUtil.h"

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	Widget wArray[numValues];
	for (int j = 0; j < numValues; j++)
		wArray[j] = Widget(data[j]);

	vector<Widget> vw;						// alternative to set<Widget>

	//...									// Setup phase: lots of 
											// insertions, few lookups
	vw.insert(vw.begin(), wArray, wArray + numValues);	// insert the ints in data
													// into v at the front
	show(vw);

	sort(vw.begin(), vw.end());				// end of Setup phase. (When
											// simulating a multiset, you
											// might prefer stable_sort
											// instead; see Item 31.)

	Widget w(222);							// object for value to look up

	//...									// start Lookup phase

	if (binary_search(vw.begin(), vw.end(), w)) 		// lookup via binary_search
		cout << "Found w(222)! " << endl;
	else
		cout << "did not find w(222) in vector." << endl;
	
	vector<Widget>::iterator i =					
		lower_bound(vw.begin(), vw.end(), w);	// lookup via lower_bound;
	if (i != vw.end() && !(w < *i ))				// see Item 45 for an explana-
		cout <<	"!(w < *i) is true" << endl;		// tion of the "!(w < *i)" test
	else
		cout <<	"!(w < *i) is false" << endl;
		

	pair<vector<Widget>::iterator,
		 vector<Widget>::iterator>  range =
		equal_range(vw.begin(), vw.end(), w);	// lookup via equal_range
	if (range.first != range.second)
		cout <<	"ranges not equal" << endl;
	else
		cout <<	"ranges equal" << endl;
		

	//...										// end Lookup phase, start
												// Reorganize phase

	sort(vw.begin(), vw.end());					// begin new Lookup phase...


	printContainer("after sorting, vw", vw);


	
	return 0;
}
