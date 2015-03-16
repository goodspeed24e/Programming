//
// A third example from ESTL Item 50
//

#include <string>
#include <vector>
#include <iostream>
#include "ESTLUtil.h"
using namespace std;

class Widget {
public:
	//...
	int readStream(istream& stream);	// readStream takes
	//...								// its parameter by
};										// reference


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<Widget*> vw;


	for_each(										// most STL platforms
		vw.begin(), vw.end(),						// try to generate a
		bind2nd(mem_fun(&Widget::readStream), cin)	// reference to a
	);												// reference in this 
													// call; such code
													// won't compile
	
	return 0;
}
