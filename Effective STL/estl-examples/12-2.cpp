//
// Example from Item 12, Lock class version
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"
#include "Widget.h"

int data[] = { -30, 102, 5, -19, 0, 5, -3000, 4000, 5, -2 };
const int numValues = sizeof data / sizeof(int);

// Dummy Mutex library:
template<typename T>
inline void getMutexFor(const T &t) {}

template<typename T>
inline void releaseMutexFor(const T &t) {}


template<typename Container>	// skeletal template for classes
class Lock {					// that acquire and release mutexes
public:							// for containers; many details
								// have been omitted
	Lock(const Container& container) // acquire mutex in the constructor
			: c(container)
	{ getMutexFor(c); }

	~Lock() { releaseMutexFor(c); } // release it in the destructor
private:
	const Container& c;
};

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<int> v;
	v.insert(v.begin(), data, data + numValues);	// insert the ints in data
													// into v at the front
	printContainer("after range insert, v", v);

	{												// create new block
		Lock<vector<int> > lock(v);					// acquire mutex
		vector<int>::iterator first5(find(v.begin(), v.end(), 5));
		if (first5 != v.end()) {
		*first5 = 0;
		}
	}												// close block, automatically
													// release mutex

	printContainer("after changing first 5 to zero, v", v);
	
	return 0;
}	
