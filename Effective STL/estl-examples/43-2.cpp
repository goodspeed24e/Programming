//
// More Examples from Item 43
//
// (comment out include of compose.h for STLPort, g++)
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"
#include "compose.h"
using namespace std;

template<typename T>
class BetweenValues:
	public unary_function<T, bool> {					// see Item 40
public:
	BetweenValues(const T& lowValue,
		const T& highValue)								// have the ctor save the
	: lowVal(lowValue), highVal(highValue)				// values to be between
	{}

	bool operator()(const T& val) const					// return whether
	{							 						// val is between the
		return val > lowVal && val < highVal;			// saved values
	}

private:
	T lowVal;
	T highVal;
};


int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<int> v;
	int x, y;

	v.insert(v.begin(), data, data + numValues);	// insert the ints in data
													// into v at the front
	printContainer("after initialization, v", v);

	x = 50; y = 56;

	vector<int>::iterator i = v.begin();			// iterate from v.begin() until an
	for( ; i != v.end(); ++i) {						// appropriate value is found or
		if (*i > x && *i < y) break;				// v.end() is reached
	}
													// i now points to the value or is
													// the same as v.end()
	if (i == v.end())
		cout << "Never found it!" << endl;
	else
		cout << "Found it! value = " << *i << endl;
	
/////////////////////////////////////////////////////////////////////////////
/// REQUIRES SGI LIBRARY ////////////////////////////////////////////////////

	{
		vector<int>::iterator i =
		find_if(v.begin(), v.end(),					// find the first value v
				compose2(	logical_and<bool>(),	// where the "and" of
					bind2nd(greater<int>(), x),		// v > x and
					bind2nd(less<int>(), y)));		// v < y
													// is true
		if (i == v.end())
			cout << "Never found it!" << endl;
		else
			cout << "Found it! value = " << *i << endl;
	}

//////////////////////////////////////////////////////////////////////////////

	{
		vector<int>::iterator i = find_if(v.begin(), v.end(), 
				BetweenValues<int>(x, y));
		if (i == v.end())
			cout << "Never found it!" << endl;
		else
			cout << "Found it! value = " << *i << endl;
	}
	
	{
		vector<int>::iterator i = find_if(v.begin(), v.end(), 
			BetweenValues<int>(x, y));
	}
	return 0;
}
