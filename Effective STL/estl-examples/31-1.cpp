//
// Examples from Item 31
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "Widget.h"

#include "ESTLUtil.h"

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

bool qualityCompare(const Widget& lhs, const Widget& rhs) 
{
	// return whether lhs's quality is greater than rhs's quality
	return lhs.getVal() > rhs.getVal();
}

bool hasAcceptableQuality(const Widget& w)
{
	// return whether w has a quality rating of 2 or better;
	return w.getVal() >= 2;
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	Widget wArray[numValues * 5];
	for (int j = 0; j < numValues * 5; j++)
		wArray[j] = Widget(data[j % numValues] + j);

	vector<Widget> widgets(wArray, wArray + numValues * 5);
	random_shuffle(widgets.begin(), widgets.end());
	
	printContainer("After init and shuffle, widgets", widgets);

/*
	sort(widgets.begin(),
		widgets.end(),			// but don't worry about
		qualityCompare);		// their order
	printContainer("\nJust plain sorted, widgets", widgets);
*/


	partial_sort(widgets.begin(),		// put the best 20 elements
				 widgets.begin() + 20,	// at the front of widgets,
					widgets.end(), 		// and make sure they're
					qualityCompare);	// in order

	printContainer("\nAfter partial sort, widgets", widgets);

	random_shuffle(widgets.begin(), widgets.end());

	nth_element(widgets.begin(),		// put the best 20 elements
				widgets.begin() + 19,	// at the front of widgets,
				widgets.end(),			// but don't worry about
				qualityCompare);		// their order

	printContainer("\nAfter reshuffle and nth_element, widgets", widgets);
	

	vector<Widget>::iterator begin(widgets.begin());	// convenience vars
	vector<Widget>::iterator end(widgets.end());		// for widgets' begin
														// and end iterators

	vector<Widget>::iterator goalPosition;				// iter indicating where
														// the widget of interest
														// is located

	// The following code finds the Widget with
	// the median level of quality

	goalPosition = begin + widgets.size() / 2;			// the widget of interest 
														// would be in the middle
														// of the sorted vector

	nth_element(begin, goalPosition, end,				// find the median quality
						qualityCompare);				// value in widgets

	cout << "\nMedian quality value: " << widgets[widgets.size() / 2] << endl;
	
	//						...							// goalPosition now points
														// to the Widget with a
														// median level of quality


	// The following code finds the Widget with
	// a level of quality at the 75th percentile

	vector<Widget>::size_type goalOffset =				// figure out how far from
		0.25 * widgets.size();							// the beginning the
														// Widget of interest is

	nth_element(begin, begin + goalOffset, end,			// find the quality value at
						qualityCompare);				// the 75th percentile

	//						...							// begin + goalOffset now points
														// to the Widget with the
														// 75th percentile level of
														// quality

	cout << "\n75th percentile value: " << widgets[.25 * widgets.size()] << endl;
	cout << "(should be same as: " << *(begin + goalOffset) << ")" << endl;

	/////////////////////////////////////////////////////////////////////////////


	vector<Widget>::iterator goodEnd =		// move all widgets satisfying
		partition(widgets.begin(),			// hasAcceptableQuality to
				widgets.end(),				// the front of widgets, and 
				hasAcceptableQuality);		// return an iterator to the first
											// widget that isn't satisfactory
	printContainer("\nAfter partition, widgets", widgets);
	

	return 0;
}
 