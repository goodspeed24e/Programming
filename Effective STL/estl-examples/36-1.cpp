//
// Example from ESTL item 36
//

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "ESTLUtil.h"
#include "Widget.h"

bool isDefective(const Widget& w)
{
	return w.getVal() % 2 == 1;	// devective == odd
}


/*
template<typename InputIterator,		// a not-quite-right
		typename OutputIterator,		// implementation of
		typename Predicate>				// copy_if
OutputIterator copy_if(InputIterator begin,
			InputIterator end,
			OutputIterator destBegin,
			Predicate p)
{
	return remove_copy_if(begin, end, not1(p));
}
*/


template<typename InputIterator,	// a correct 
	typename OutputIterator,		// implementation of
	typename Predicate>				// copy_if
OutputIterator copy_if(InputIterator begin,
		InputIterator end,
		OutputIterator destBegin,
		Predicate p)
{
	while (begin != end) {
		if (p(*begin)) *destBegin++ = *begin;
		++begin;
	}
	return destBegin;
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;


	vector<Widget> widgets;

	for (int j = 0; j < 10; ++j)	// insert some Widgets
		widgets.push_back(Widget(j));

	printContainer("widgets", widgets);

	copy_if(widgets.begin(), widgets.end(),		// this won't compile; 
		ostream_iterator<Widget>(cerr, " "),	// there is no copy_if
		isDefective);							// in the STL


	return 0;
}
