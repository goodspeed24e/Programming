//
// Example from ESTL Item 21
//

#include <set>
#include <iostream>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	set<int, less_equal<int> > s;	// s is sorted by "<="

	s.insert(10);					// insert the value 10

	s.insert(10);

	show(s);						// I (LZ) am getting tired of typing 'printContainer("name",'...


	return 0;
}
