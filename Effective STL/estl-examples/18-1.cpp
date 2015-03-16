//
// Example from ESTL Item 18
//

#include <string>
#include <vector>
#include <iostream>
#include "ESTLUtil.h"

class T {};

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<T> c(10);
	
	T *p = &c[0];					// initialize a T* with the address
									// of whatever operator[] returns


	vector<bool> v;

	bool *pb = &v[0];				// initialize a bool* with the address of
									// what vector<bool>::operator[] returns



	return 0;
}
