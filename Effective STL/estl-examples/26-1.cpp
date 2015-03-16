//
// Example from Item 26
//

#include <iostream>
#include <deque>

#include "ESTLUtil.h"

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

int main()
{
	using namespace std;
	using namespace ESTLUtils;


	typedef deque<int> IntDeque;					// STL container and 
	typedef IntDeque::iterator Iter;				// iterator types are easier
	typedef IntDeque::const_iterator ConstIter;		// to work with if you
													// use some typedefs
	Iter i;		
	ConstIter ci;

	deque<int> d;			// make i and ci point into
	i = d.begin();			// the same container
	ci = d.begin();
	
	if (i == ci)									// compare an iterator 
		cout << "Iterators are equal" << endl;		// and a const_iterator
	else
		cout << "Iterators are not equal" << endl;	


	if (ci == i)								// workaround for when the 
		cout << "Iterators are equal" << endl;	// comparison above won't compile
	else
		cout << "Iterators are not equal" << endl;	

	
	if (ci + 3 <= i)							// workaround for when the above
		cout << "Iterators are equal" << endl;	// won't compile
	else
		cout << "Iterators are not equal" << endl;	

	return 0;
}
