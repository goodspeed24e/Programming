//
// Fifth example from Item 7 ("SpecialString"):
//

#include <iostream>
#include <deque>
#include <vector>

#include "ESTLUtil.h"
#include "Widget.h"

using namespace std;
using namespace ESTLUtils;

struct DeleteObject {		// templatization and base
							// class removed here
	template<typename T>	// templatization added here
	void operator()(const T* ptr) const
	{ delete ptr; }
};


class SpecialString: public string
{
public:
	SpecialString(const char *s) : string(s) {}

				// Now we'll see this d'tor run
	~SpecialString() { cout << "destroying a SpecialString..." << endl; }

				// assume all sorts of dynamic stuff lives here...
};

void doSomething()
{
	deque<SpecialString*> dssp;

	dssp.push_back(new SpecialString("hi"));
	dssp.push_back(new SpecialString("there"));
	dssp.push_back(new SpecialString("dude"));

	for_each( dssp.begin(), dssp.end(),	
		DeleteObject());				// ah! well-defined behavior!
}

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	doSomething();

	return 0;
}
