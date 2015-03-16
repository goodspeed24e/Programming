//
// Examples from ESTL Item 21, continued
//

#include <set>
#include <iostream>
#include "ESTLUtil.h"
using namespace std;

struct StringPtrGreater:					// highlights show how 
	public binary_function<const string*,	// this code was changed
					const string*,			// from page 89. Beware,
					bool> {					// this code is flawed!

	bool operator()(const string *ps1, const string *ps2) const
	{
		return !( *ps1 < *ps2);				// just negate the old test
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
	ssp.insert(new string("Wombat"));		// but does because of the faulty comparison
	ssp.insert(new string("Lemur"));
	ssp.insert(new string("Penguin"));

	{ // comes out in "random" order:
	for (set<string*, StringPtrGreater>::const_iterator i = ssp.begin();		// you expect to see
			 i != ssp.end();								// this: "Anteater",
			 ++i)											// "Lemur", "Penguin", 
		cout << **i << endl;								// "Wombat"
	}	

	for_each(ssp.begin(), ssp.end(), print);			/// invoke print on each
						// element in ssp


	return 0;
}
