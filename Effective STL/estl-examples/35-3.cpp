//
// Yet More from ESTL Item 35
//

#include <string>
#include <iostream>
#include "ESTLUtil.h"
using namespace std;


int ciCharCompare(char c1, char c2)		// case-insensitively compare chars
{										// c1 and c2, returning -1 if c1 < c2,
										// 0 if c1==c2, and 1 if c1 > c2

	int lc1 = tolower(static_cast<unsigned char>(c1));		// see below for
	int lc2 = tolower(static_cast<unsigned char>(c2));		// info on these
															// statements

	if (lc1 < lc2) return -1;

	if (lc1 > lc2) return 1;

	return 0;
}

int ciStringCompareImpl(const string& s1,			// see below for
						const string& s2);			// implementation

int ciStringCompareImpl(const string& s1, const string& s2)
{
	typedef pair<string::const_iterator,			// PSCI = "pair of
				string::const_iterator> PSCI;		// string::const_iterator"

	 PSCI p = mismatch(								// see below for an
		s1.begin(), s1.end(),						// explanation of why
		s2.begin(),									// we need not1; see
		not2(ptr_fun(ciCharCompare)));				// Item 41 for why we
													// need ptr_fun

	if (p.first == s1.end()) {						// if true, either s1 and
		if (p.second == s2.end()) return 0;			// s2 are equal or
		else return -1;								// s1 is shorter than s2
	}

	return ciCharCompare(*p.first, *p.second);		// the relationship of the
}													// strings is the same as
													// that of the
													// mismatched chars


bool ciCharLess(char c1, char c2)							// return whether c1
{															// precedes c2 in a case-
	return													// insensitive comparison;
		tolower(static_cast<unsigned char>(c1)) <			// Item 46 explains why a
		tolower(static_cast<unsigned char>(c2));			// function object might
}															// be preferable to this
															// function

/*bool ciStringCompare(const string& s1, const string& s2)
{
	return lexicographical_compare(	s1.begin(), s1.end(),	// see below for
							s2.begin(), s2.end(),			// a discussion of
							ciCharLess);					// this algorithm
}															// call
*/

int ciStringCompare(const string& s1, const string& s2)
{
	return stricmp(s1.c_str(), s2.c_str());					// the function name on
}						// your system might
							// not be stricmp
int main()
{
	using namespace std;
	using namespace ESTLUtils;

	string s1("tHiS");
	string s2("tHIS");

	cout << "S1=" << s1 << "; s2=" << s2 << endl;
	if (ciStringCompare(s1,s2) == 0)
		cout << "They're the same!" << endl;
	else
		cout << "They're different!" << endl;
	

	return 0;
}
