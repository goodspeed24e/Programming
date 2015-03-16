//
// More from ESTL Item 37
//

#include <list>
#include <iostream>
#include <numeric>
#include <string>
#include "ESTLUtil.h"
using namespace std;

string::size_type									// see below for info
stringLengthSum(string::size_type sumSoFar,			// on string::size_type 
					const string& s)
{
	return sumSoFar + s.size();
}

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	const int vals[] = { 1, 2, 3, 4, 5};
	const int nvals = sizeof vals / sizeof(int);

	cout << "Enter some integer values separated by spaces, control-Z to quit: " << endl;

	cout << "The sum of the ints on the standard input is "		// print the sum of
		<< accumulate(		istream_iterator<int>(cin),			// the ints in cin
				istream_iterator<int>(), 0) << endl;
	
	string s1("this is a");
	string s2("test of the");
	string s3("emergency broadcast system");

	string::size_type sum = 0;
	sum = stringLengthSum(sum, s1);
	sum = stringLengthSum(sum, s2);
	sum = stringLengthSum(sum, s3);

	cout << "sum of lengths = " << sum << endl;
	
	return 0;
}
