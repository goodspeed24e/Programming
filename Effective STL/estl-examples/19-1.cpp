//
// Example from ESTL Item 19
//

#include <string>
#include <set>
#include <iostream>
#include <cstring>
#include <functional>
#include "ESTLUtil.h"
using namespace std;

class TimeStamp {};

class Widget {
public:

private:
	TimeStamp lastAccessed;

};


bool operator==(const Widget& , const Widget& )
{
	// code that ignores the lastAccessed field
	return true;
}


/*int ciStringCompare(const std::string &lhs, const std::string &rhs)
{
	return stricmp(lhs.c_str(), rhs.c_str()); // the function name on
}
*/

bool ciCharLess(char c1, char c2)						// return whether c1
{														// precedes c2 in a case-
	return												// insensitive comparison;
		tolower(static_cast<unsigned char>(c1)) <		// Item 46 explains why a
		tolower(static_cast<unsigned char>(c2));		// function object might
}														// be preferable to this
														// function

bool ciStringCompare(const string& s1, const string& s2)
{
	return lexicographical_compare(s1.begin(), s1.end(),	// see below for
		s2.begin(), s2.end(),								// a discussion of
		ciCharLess);										// this algorithm
}															// call


struct CIStringCompare:							// class for case-insensitive
	public										// string comparisons;
	binary_function<string, string, bool> {		// see Item 40 for info on
												// this base class
	bool operator()(const string& lhs,
					const string& rhs) const
	{
		return ciStringCompare(lhs, rhs);		// see Item 35 for how
	}											// ciStringCompare is
												// implemented

};

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	set<string, CIStringCompare> ciss;	 		// ciss = “case-insensitive
												// string set”


	ciss.insert("Persephone");					// a new element is added to the set

	ciss.insert("persephone");					// no new element is added to the set


	printContainer("ciss", ciss);

	if (ciss.find("persephone") != ciss.end()) 		// this test will succeed
		cout << "set::find found persephone" << endl;

	if (find(ciss.begin(), ciss.end(),
				"persephone") != ciss.end()) 		// this test will fail
		cout << "algorithm find found persephone" << endl;

	return 0;
}
