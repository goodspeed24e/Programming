//
// Last from ESTL Item 21
//

#include <set>
#include <iostream>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	multiset<int, less_equal<int> > s;	// s is still sorted by "<="

	s.insert(10);						// insert 10A

	s.insert(10);						// insert 10B

	show(s);							// I (LZ) am getting tired of typing 'printContainer("name",'...


	return 0;
}
