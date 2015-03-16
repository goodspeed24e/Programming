//
// Examples from ESTL Appendix B (microsoft 4/5 compatible)
//

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <iostream>
#include <algorithm>
#include "ESTLUtil.h"
#include "Widget.h"
using namespace std;

template<typename T,										  // template for a custom
	    typename Allocator = allocator<T> >					  // STL-compatible
class SpecialContainer : public std::vector<T, Allocator>{ }; // container

template <class T, class Allocator = allocator<T> >
class vector_demo {
public:
		// ...
		typedef std::vector<T, Allocator>::iterator iterator;
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);
		// ...
};



int main()
{
	using namespace std;
	using namespace ESTLUtils;


	vector<Widget> vw1, vw2;

	for (int j = 0; j < 10; ++j) {				// insert some Widgets
		vw1.push_back(Widget(j));
		vw2.push_back(Widget(j + 100));
	}

	show2(vw1, vw2);
	
	vw1.insert(vw1.end(), vw2.begin(), vw2.end());      // append to vw1 a copy
														// of the Widgets in vw2

	show(vw1);
	
	cout << "----------------------------------------------" << endl;

	vector<Widget> vw;
	deque<Widget> dw;

	{
		for (int j = 0; j < 10; ++j) {				// insert some Widgets
			vw.push_back(Widget(j));
			dw.push_back(Widget(j + 100));
		}
	}

	show(vw);
	
/*
	vw.insert(vw.end(), dw.begin(), dw.end());		// append to vw a copy
	show(vw);										// of the Widgets in dw
*/
	cout << "----------------------------------------------" << endl;

	{
		vector<Widget> vw;
		list<Widget> lw;

		for (int j = 0; j < 10; ++j) {				// insert some Widgets
			vw.push_back(Widget(j));
			lw.push_back(Widget(j + 100));
		}

		show(vw);
/*
		vw.insert(vw.begin(), lw.begin(), lw.end());	// prepend to vw a copy
		show(vw);										// of the Widgets in lw
*/
		set<Widget> sw;

		for (int j2 = 0; j2 < 10; ++j2)					// insert some Widgets
			sw.insert(Widget(j2 * 1000));

/*		vw.insert(vw.begin(), sw.begin(), sw.end());    // prepend to vw a copy
		show(vw);										// of the Widgets in sw
*/
	}


	cout << "----------------------------------------------" << endl;

	{
		SpecialContainer<Widget> scw;

		for (int j = 0; j < 10; ++j)					// insert some Widgets
			scw.push_back(Widget(j));

		vw.insert(vw.end(), scw.begin(), scw.end());    // append to vw a copy
														// of the Widgets in scw
		show(vw);
	}

	cout << "----------------------------------------------" << endl;

	{
//		vector<Widget> vw((istream_iterator<Widget>(cin)),  // construct vw
//		vector<Widget> vw(istream_iterator<Widget>(cin),	// construct vw
//						istream_iterator<Widget>());        // from the
															// Widgets in cin;

		vector<Widget> vw;
		for (int j = 0; j < 10; ++j)		 				// insert some Widgets
			vw.push_back(Widget(j));
															// see Item 6


		list<Widget> lw;
															// assign vw’s 
/*
		lw.assign(vw.rbegin(), vw.rend());                  // contents to lw
															// (in reverse
															// order)
		show(lw);
*/
		
		SpecialContainer<Widget> scw;
		show(scw);

		scw.push_back(Widget(2222));                        // insert at the end
		scw.push_back(Widget(2223));						// of scw a copy of
/*
		scw.insert(scw.end(), lw.begin(), lw.end());        // the Widgets in lw
		show(scw);
*/
		}

	cout << "----------------------------------------------" << endl;

	{
		vector<Widget> vw;                                                                      // default-construct vw;
		cout << "enter some Widget data, ^z to end:" << endl;
		copy(istream_iterator<Widget>(cin),                                          // then copy the
			 istream_iterator<Widget>()              ,                               // Widgets in cin into it
			 back_inserter(vw));
		cout << endl;
		show(vw);

		list<Widget> lw; 
		// ...
		lw.clear();					                     // eliminate lw’s old
		copy(vw.rbegin(), vw.rend(), back_inserter(lw)); // Widgets; copy over
														 // vw’s Widgets (in
														 // reverse order)
		show(lw);

		SpecialContainer<Widget> scw;
		// ...             
		copy(lw.begin(), lw.end(),                       // copy lw’s Widgets to
             inserter(scw, scw.end()));                  // the end of scw
		show(scw);
	}

	return 0;
}
