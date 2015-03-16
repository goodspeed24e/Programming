//
// Example from ESTL Item 39
//

#include <iostream>
#include <vector>
#include "ESTLUtil.h"
#include "Widget.h"

using namespace std;


class BadPredicate:										// see Item 40 for info
	public unary_function<Widget, bool> {				// on the base class
public:
	BadPredicate(): timesCalled(0) {}					// init timesCalled to 0

	bool operator()(const Widget&)
	{ return ++timesCalled == 3; }

private:
	size_t timesCalled;
};

/*
template <typename FwdIterator, typename Predicate>
FwdIterator remove_if(FwdIterator begin, FwdIterator end, Predicate p) 
{ 
	begin = find_if(begin, end, p); 

	if (begin == end) 		return begin; 
	else { 
		FwdIterator next = begin; 
		return remove_copy_if(++next, end, begin, p); 
	} 
} 
*/


/* Grasshopper: does a Bad BadPredicate make a "good" Predicate???
class BadPredicate:		
	public binary_function<Widget, Widget, bool> {				
public:			

	bool operator()(const Widget&, const Widget&) const
	{
		return ++timesCalled == 3;			// error! can't change local data
	}										// in a const member function

private:
	size_t timesCalled;
	//...

};
*/

bool anotherBadPredicate(const Widget&, const Widget&)
{
	static int timesCalled = 0;				// No! No! No! No! No! No! No! 
	return ++timesCalled == 3;				// Predicates should be pure functions,
}					// and pure functions have no state



int main()
{
	using namespace std;
	using namespace ESTLUtils;


	vector<Widget> vw;					// create vector and put some 
	vw.push_back(Widget(1));			// Widgets into it
	vw.push_back(Widget(2));
	vw.push_back(Widget(3));
	vw.push_back(Widget(4));
	vw.push_back(Widget(5));
	vw.push_back(Widget(6));			// let's see if the bad predicate removes this...
	vw.push_back(Widget(7));

	printContainer("vw before erase", vw);

	vw.erase(remove_if(	vw.begin(),		// eliminate the third Widget;
		vw.end(),						// see Item 32 for info on how
		BadPredicate()),				// erase and remove_if relate
		vw.end());

	printContainer("vw after erase", vw);



	return 0;
}
