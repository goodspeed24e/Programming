//
// More examples from ESTL Item 8
//

#include <iostream>
#include <vector>
#include <memory>
#include "ESTLUtil.h"
#include "Widget.h"
using namespace std;

bool widgetAPCompare(const auto_ptr<Widget>& lhs,
					   const auto_ptr<Widget>&rhs)
{
	return *lhs < *rhs; // for this example, assume that
}						// operator< exists for Widgets

ostream &operator<<(ostream &os, const auto_ptr<Widget> &wp)
{
	return os << *wp;
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	auto_ptr<Widget> pw1(new Widget(1));
	auto_ptr<Widget> pw2(new Widget(2));
	auto_ptr<Widget> pw3(new Widget(3));
	auto_ptr<Widget> pw4(new Widget(4));

	
	vector<auto_ptr<Widget> > widgets; // create a vector and then fill it
	widgets.push_back(pw1);			   // with auto_ptrs to Widgets;
	widgets.push_back(pw2);			   // remember that this should
	widgets.push_back(pw3); 		   // not compile!
	widgets.push_back(pw4);
										

	sort( widgets.begin(), widgets.end(), // sort the vector
		  widgetAPCompare);

	printContainer("widgets",widgets);

	return 0;
}
