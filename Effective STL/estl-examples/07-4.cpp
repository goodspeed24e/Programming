//
// Fourth example from Item 7 ("SpecialString"):
//

#include <iostream>
#include <deque>
#include <vector>

#include "ESTLUtil.h"
#include "Widget.h"

using namespace std;
using namespace ESTLUtils;

template<typename T>
struct DeleteObject:								// Item 40 describes why
			public unary_function<const T*, void> { // this inheritance is here
	void operator()(const T* ptr) const
	{ delete ptr; }
};

class SpecialString: public string
{
public:
	SpecialString(const char *s) : string(s) {}

			// In this program, we'll never see the d'tor run
	~SpecialString() { cout << "destroying a SpecialString..." << endl; }

			// assume all sorts of dynamic stuff lives here...
};

void doSomething()
{
	deque<SpecialString*> dssp;

	dssp.push_back(new SpecialString("hi"));
	dssp.push_back(new SpecialString("there"));
	dssp.push_back(new SpecialString("dude"));

	for_each( dssp.begin(), dssp.end(),	// undefined behavior! Deletion
			  DeleteObject<string>());	// of a derived object via a base
}										// class pointer where there is
										// no virtual destructor

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	doSomething();

	return 0;
}
