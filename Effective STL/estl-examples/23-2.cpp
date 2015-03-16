//
// More Examples from Item 23
//

#include <iostream>
#include <vector>
#include <string>
#include "Widget.h"

#include "ESTLUtil.h"
using namespace std;

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

typedef pair<string, int> Data;						// type held in the "map"
													// in this example

class DataCompare {									// class for comparison
public:												// functions

	bool operator()(const Data& lhs,				// comparison func
					const Data& rhs) const			// for sorting
	{ return keyLess(lhs.first, rhs.first); 	}			

	bool operator()(const Data& lhs,				 // comparison func
					const Data::first_type& k) const // for lookups 
	{ return keyLess(lhs.first, k); }				 // (form 1)

	bool operator()(const Data::first_type& k,		// comparison func
					const Data& rhs) const			// for lookups 
	{ return keyLess(k, rhs.first); }				// (form 2)

private:
	bool keyLess(const Data::first_type& k1,		// the "real" 
				 const Data::first_type& k2) const	// comparison
	{ return k1 < k2; }								// function

};


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	char *dummy = "dummy";		// pain in the butt not to be able to just say "dummy
								// as an arg to make_pair...
	Data dArray[numValues];
	for (int j = 0; j < numValues; j++)
		dArray[j] = Data(dummy, data[j]);

	vector<Data> vd;									// alternative to
														// map<string, int>

	//...												// Setup phase: lots of 
														// insertions, few lookups
	vd.insert(vd.begin(), dArray, dArray + numValues);	// insert the ints in data
														// into v at the front
	sort(vd.begin(), vd.end(), DataCompare());			// end of Setup phase. (When
														// simulating a multimap, you
														// might prefer stable_sort
														// instead; see Item 31.)

	printContainer("After setup, vd", vd);

	string s("foobar");						// object for value to look up

	//...									// start Lookup phase

	if (binary_search(vd.begin(), vd.end(), s,
					DataCompare())) 		// lookup via binary_search
		cout << "Found s! " << endl;
	else
		cout << "did not find s." << endl;

	Data w(make_pair(dummy, 55));

	vector<Data>::iterator i =					
		lower_bound(vd.begin(), vd.end(), s,
					DataCompare());			// lookup via lower_bound;
	if (i != vd.end() && !(s < i->first))	// again, see Item 45 for info
		cout <<	"!(s < i->first) is true" << endl;	// on the "!(s < i->first)" test
	else
		cout <<	"!(s < i->first) is false" << endl;


	pair<vector<Data>::iterator,
			vector<Data>::iterator> range =
		equal_range(vd.begin(), vd.end(), s,
					DataCompare());			// lookup via equal_range
	if (range.first != range.second) 
		cout <<	"ranges not equal" << endl;
	else
		cout <<	"ranges equal" << endl;

	//...										// end Lookup phase, start
												// Reorganize phase

	sort(vd.begin(), vd.end(), DataCompare());	// begin new Lookup phase...


	printContainer("After sorting, vd", vd);




	return 0;
}
