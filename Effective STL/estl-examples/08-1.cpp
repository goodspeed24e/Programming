//
// Example from ESTL Item 8
//

#include <iostream>
#include <memory>
#include "ESTLUtil.h"
#include "Widget.h"


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	auto_ptr<Widget> pw1(new Widget);	// pw1 points to a Widget
	auto_ptr<Widget> pw2(pw1);			// pw2 points to pw1’s Widget;
										// pw1 is set to NULL. (Ownership
										// of the Widget is transferred
										// from pw1 to pw2.)
	pw1 = pw2;							// pw1 now points to the Widget
										// again; pw2 is set to NULL

	return 0;
}
