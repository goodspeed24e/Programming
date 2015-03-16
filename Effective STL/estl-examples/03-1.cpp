//
// Example from ESTL item 3
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "ESTLUtil.h"
#include "Widget.h"

class SpecialWidget:			// SpecialWidget inherits from Widget
	public Widget
{
public:
	void draw(double ScaleFactor = 1) const;
};					

void SpecialWidget::draw(double ScaleFactor) const
{
	std::cout << "Drawing Special Widget (val = " << val << ") using ScaleFactor " <<
			ScaleFactor << "..." << std::endl;
}

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<Widget> vw;
	vw.push_back(Widget());		// "Vanilla" Widget

	SpecialWidget sw;			// Special Widget
	vw.push_back(sw);			// sw is copied as a base class
								// object into vw. Its specialness
								// is lost during the copying.	

	vw[0].draw(3);				// IS a Widget, draws as one
	vw[1].draw(3);				// WAS a SpecialWidget, now just a Widget


	const size_t maxNumWidgets = 223;

	{
		Widget w[maxNumWidgets];	// create an array of maxNumWidgets
									// Widgets, default-constructing each one
	}

	{
		vector<Widget> vw; // create a vector with zero Widget
						   // objects that will expand as needed
	}

	{
		vector<Widget> vw;
		vw.reserve(maxNumWidgets); // see Item 14 for details on reserve
	}

	return 0;
}
