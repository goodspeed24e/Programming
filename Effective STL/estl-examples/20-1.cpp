//
// Example from ESTL Item 20
//

#include <set>
#include <iostream>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	set<string*> ssp;						// ssp = “set of string ptrs”
//	set<string*, less<string*> > ssp;
//	set<string*, less<string*>, allocator<string*> > ssp;

	ssp.insert(new string("Anteater"));
	ssp.insert(new string("Wombat"));
	ssp.insert(new string("Lemur"));
	ssp.insert(new string("Penguin"));

	{
	for (set<string*>::const_iterator i = ssp.begin();		// you expect to see
			 i != ssp.end();								// this: "Anteater",
			 ++i)											// "Lemur", "Penguin", 
		cout << *i << endl;									// "Wombat"
	}
/*
	copy(ssp.begin(), ssp.end(),						// copy the strings in
			ostream_iterator<string>(cout, "\n"));		// ssp to cout (but this
*/														// won't compile)

	{ // comes out in "random" order:
	for (set<string*>::const_iterator i = ssp.begin();		// you expect to see
			 i != ssp.end();								// this: "Anteater",
			 ++i)											// "Lemur", "Penguin", 
		cout << **i << endl;								// "Wombat"
	}	



	return 0;
}
