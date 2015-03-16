//
// Example from ESTL Item 10 (G++ specific)
//

#include <string>
#include <iostream>
#include "SpecialAllocator.h"
#include <list>
#include <set>
#include "ESTLUtil.h"
#include "Widget.h"


/*
template<typename T>							// the standard allocator is declared
class allocator {								// like this, but this could be a user-
public:											// written allocator template, too

	template<typename U>
	struct rebind {
		typedef allocator<U> other;
	};

//	...
};
*/

int main()
{
	using namespace std;
	using namespace ESTLUtils;
	using namespace MyLib;

	typedef SpecialAllocator<Widget> SAW;		// SAW = "SpecialAllocator
												// for Widgets"

	list<Widget, SAW> L1;
	list<Widget, SAW> L2;

	L1.push_back(Widget(10));
	L1.push_back(Widget(20));
	L2.push_back(Widget(30));
	L2.push_back(Widget(40));

	L1.splice(L1.begin(), L2);					// move L2's nodes to the
												// front of L1

	printContainers("L1",L1,"L2",L2);


	/*********************************************/

	list<int> L;		// same as list<int, allocator<int> >;
						// allocator<int> is never asked to
						// allocate memory!

	set<Widget, SAW> s;	// recall that SAW is a typedef for
						// SpecialAllocator<Widget>; no
						// SAW will ever allocate memory!


	return 0;
}

/*
template<typename T,							// possible list
		typename Allocator = allocator<T> >		// implementation
class list {
private:

	Allocator alloc;							// allocator for objects of type T

	struct ListNode {							// nodes in the linked list
		T data;
		ListNode *prev;
		ListNode *next;
	};
//	...
};

*/