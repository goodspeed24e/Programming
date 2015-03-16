//
// More Examples from Item 5
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"
#include "Widget.h"

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	{
		vector<int> v;
		
		v.insert(v.begin(), data, data + numValues); // insert the ints in data
													 // into v at the front
		printContainer("after range insert, v", v);
	}

	{
		vector<int> v;
		
		vector<int>::iterator insertLoc(v.begin());
		for (int i = 0; i < numValues; ++i) {
			insertLoc = v.insert(insertLoc, data[i]);
			insertLoc++;
		}
		printContainer("after insert loop, v", v);
	}

	{
		vector<int> v;
		copy(data, data + numValues, inserter(v, v.begin()));
		printContainer("using copy w/inserter, v", v);
	}

	
	return 0;
}
