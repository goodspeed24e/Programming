//
// Example from ESTL Item 2, without typedefs
//

#include <vector>
#include <iostream>

#include "ESTLUtil.h"
#include "Widget.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<Widget> vw;
	Widget bestWidget(3);

	for (int j = 0; j < 10; ++j)	// insert some Widgets
		vw.push_back(Widget(j));

	vector<Widget>::iterator i = find(vw.begin(), vw.end(), bestWidget);

	cout << "We found the Widget with value: " << *i << endl;

	return 0;
}
