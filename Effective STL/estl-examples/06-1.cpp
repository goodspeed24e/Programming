//
// Example from ESTL Item 6
//
// Fails under MSVC/native lib, STLPort
//

#include <list>
#include <iostream>
#include <fstream>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	ifstream dataFile("ints.dat");


/* incorrect, but works with some compilers: 
	{
		list<int> data(istream_iterator<int>(dataFile), // warning! this doesn’t do
					   istream_iterator<int>());		// what you think it does
		cout << "First value in the list is " << *data.begin() << endl;
	}
*/

	
/* correct, but doesn't work with some compilers:
	{
		list<int> data((istream_iterator<int>(dataFile)),	// note new parens
					   istream_iterator<int>());			// around first argument
															// to list’s constructor
		cout << "First value in the list is " << *data.begin() << endl;
	}
*/
	

/* should always work: */
	{
		istream_iterator<int> dataBegin(dataFile);
		istream_iterator<int> dataEnd;
		list<int> data(dataBegin, dataEnd);	

		cout << "First value in the list is " << *data.begin() << endl;
	}
	return 0;
}
