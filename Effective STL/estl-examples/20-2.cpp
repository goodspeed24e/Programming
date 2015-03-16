//
// Examples from ESTL Item 20, continued
//

#include <set>
#include <iostream>
#include "ESTLUtil.h"
using namespace std;

struct StringPtrLess:
	public binary_function<const string*,		// see Item 40 for the
					const string*,				// reason for this base
					bool> {						// class
	bool operator()(const string *ps1, const string *ps2) const
	{
		return *ps1 < *ps2;
	}
};

void print(const string *ps)					// print to cout the
{												// object pointed to
	cout << *ps << endl;						// by ps
}


struct Dereference {							// when functors of this type are
												// passed a T*, they return a const T&
	template <typename T>
	const T& operator()(const T *ptr) const		// this member function 
	{											// template makes
		return *ptr;							// Dereference unadaptable;
	}											// see Item 40 for details

};


bool stringPtrLess(const string* ps1,	// would-be comparison 
				const string* ps2)		// function for string* 
{										// pointers to be sorted by 
	return *ps1 < *ps2;					// string value
}

struct DereferenceLess {
	template <typename PtrType>
	bool operator()(PtrType pT1,		// parameters are passed by
					PtrType pT2) const 	// value, because we expect them
	{									// to be (or to act like) pointers
		return *pT1 < *pT2;
	}
};


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	set<string*, StringPtrLess> ssp;		// create a set of strings and order
											// them as defined by StringPtrLess


	ssp.insert(new string("Anteater"));
	ssp.insert(new string("Wombat"));
	ssp.insert(new string("Lemur"));
	ssp.insert(new string("Penguin"));

/*
	{
	for (set<string*>::const_iterator i = ssp.begin();		// you expect to see
			 i != ssp.end();								// this: "Anteater",
			 ++i)											// "Lemur", "Penguin", 
		cout << *i << endl;									// "Wombat"
	}

	copy(ssp.begin(), ssp.end(),						// copy the strings in
			ostream_iterator<string>(cout, "\n"));		// ssp to cout (but this
*/														// won't compile)

	{ // comes out in "random" order:
	for (set<string*, StringPtrLess>::const_iterator i = ssp.begin();		// you expect to see
			 i != ssp.end();								// this: "Anteater",
			 ++i)											// "Lemur", "Penguin", 
		cout << **i << endl;								// "Wombat"
	}	

	for_each(ssp.begin(), ssp.end(), print);			/// invoke print on each
						// element in ssp


	transform(ssp.begin(), ssp.end(),			// "transform" each element
			ostream_iterator<string>(cout,"\n"),		// in ssp by dereferencing it,
			Dereference());						// writing the results to cout

/*
	{
	set<string, stringPtrLess> ssp;						// attempt to use stringPtrLess
														// as ssp's comparison function
														// (this won't compile)
	}
*/
	{
	set<string*, DereferenceLess> ssp;					// behaves the same as 
														// set<string*, StringPtrLess>
	}

	return 0;
}
