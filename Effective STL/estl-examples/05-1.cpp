//
// Examples from Item 5
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"
#include "Widget.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<Widget> v1, v2;
	
	for (int i = 0; i < 10; i++)
	{
		Widget w(i);
		v1.push_back(w);
		v2.push_back(w);
	}

	printContainers("v1", v1, "v2", v2);

	v1.clear();
	for (vector<Widget>::const_iterator ci = v2.begin() + v2.size() / 2;
			 ci != v2.end(); ++ci)
		v1.push_back(*ci);

	printContainer("after push_back loop, v1", v1);

	v1.clear();
	copy(v2.begin() + v2.size() / 2, v2.end(), back_inserter(v1));
	printContainer("after copy loop, v1", v1);

	v1.clear();
	v1.insert(v1.end(), v2.begin() + v2.size() / 2, v2.end());
	printContainer("after insert loop, v1", v1);

	return 0;
}
