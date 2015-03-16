//
// Examples from ESTL Item 21, continued
//

#include <set>
#include <iostream>
#include "ESTLUtil.h"
using namespace std;

struct StringPtrGreater:					// this is a valid 
	public binary_function<const string*,	// comparison type for 
					const string*,			// associative containers
					bool> {
	bool operator()(const string *ps1, const string *ps2) const
	{
		return *ps1 > *ps2;					// use ">" instead of "! <"
	}
};

void print(const string *ps)				// print to cout the
{											// object pointed to
	cout << *ps << endl;					// by ps
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	set<string*, StringPtrGreater> ssp;		// create a set of strings and order
											// them as defined by StringPtrLess

	ssp.insert(new string("Anteater"));
	ssp.insert(new string("Wombat"));		// an extra Wombat, *shouldn't* show up...
	ssp.insert(new string("Wombat"));		// and now indeed does not.
	ssp.insert(new string("Lemur"));
	ssp.insert(new string("Penguin"));

	{ // comes out in "random" order:
	for (set<string*, StringPtrGreater>::const_iterator i = ssp.begin();		// you expect to see
			 i != ssp.end();								// this: "Anteater",
			 ++i)											// "Lemur", "Penguin", 
		cout << **i << endl;								// "Wombat"
	}	

	for_each(ssp.begin(), ssp.end(), print);			// invoke print on each
														// element in ssp


	return 0;
}
