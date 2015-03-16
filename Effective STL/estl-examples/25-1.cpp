//
// Example from ESTL Item 25
//

#include <list>
#include <iostream>
#include <hash_set>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;


	const int vals1[] = { 1, 25, 3, 47, -5};

	const int nvals1 = sizeof vals1 / sizeof(int);

//	hash_set<int> intTable;					// create a hashed set of ints


	hash_set<int> intTable(vals1, vals1 + nvals1);
	
	printContainer("After init, intTable", intTable);

	return 0;
}
