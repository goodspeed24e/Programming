//
// Example from ESTL item 2, using "ciStringCompare"
//

#include <vector>
#include <iostream>

#include "ESTLUtil.h"
#include "Widget.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;


	typedef vector<Widget> WidgetContainer;
	typedef WidgetContainer::iterator WCIterator;
	WidgetContainer vw;
	Widget bestWidget(3);

	for (int j = 0; j < 10; ++j)	// insert some Widgets
		vw.push_back(Widget(j));

	WCIterator i = find(vw.begin(), vw.end(), bestWidget);

	cout << "We found the Widget with value: " << *i << endl;

	return 0;
}
