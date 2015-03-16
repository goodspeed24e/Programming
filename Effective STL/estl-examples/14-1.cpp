//
// Example from Item 14
//
// Fails under MSVC/native lib, g++ (string lacks push_back)
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	{
		vector<int> v;
		for (int i = 1; i <= 1000; ++i) v.push_back(i);

	}

	{
		vector<int> v;
		v.reserve(1000);
		for (int i = 1; i <= 1000; ++i) v.push_back(i);
	}

	{
		string s;
		s = "This is a test";
		if (s.size() < s.capacity()) {
			s.push_back('x');
		}
	}

	return 0;
}
