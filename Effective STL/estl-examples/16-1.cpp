//
// Examples from Item 16
//

#include <iostream>
#include <vector>
#include <cstring>

#include "ESTLUtil.h"

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

void doSomething(const int* pInts, size_t numInts)
{
	int sum = 0;
	for (size_t i = 0; i < numInts; i++)
		sum += pInts[i];
	std::cout << "Sum of ints in the array is " << sum << std::endl;
}


void doSomething(const char *pString)
{
	std::cout << "in doSomething, length of the string is: " << strlen(pString) << std::endl;
}

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<int> v;
	v.insert(v.begin(), data, data + numValues);	// insert the ints in data
													// into v at the front
	printContainer("after range insert, v", v);

	doSomething(&v[0], v.size());
	
	if (!v.empty()) {
		doSomething(&v[0], v.size());
	}

	string s("this is a test");
	doSomething(s.c_str());

	return 0;
}
