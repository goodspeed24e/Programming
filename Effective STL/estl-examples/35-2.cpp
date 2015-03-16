//
// More from ESTL Item 35
//

#include <string>
#include <iostream>
#include "ESTLUtil.h"
using namespace std;


bool ciCharLess(char c1, char c2)							// return whether c1
{															// precedes c2 in a case-
	return													// insensitive comparison;
		tolower(static_cast<unsigned char>(c1)) <			// Item 46 explains why a
		tolower(static_cast<unsigned char>(c2));			// function object might
}															// be preferable to this
															// function


bool ciStringCompare(const string& s1, const string& s2)
{
	return lexicographical_compare(	s1.begin(), s1.end(),	// see below for
							s2.begin(), s2.end(),			// a discussion of
							ciCharLess);					// this algorithm
}															// call


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
