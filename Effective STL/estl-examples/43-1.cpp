//
// Example from ESTL Item 43
//
// Fails under MSVC/native lib (mem_fun_ref problem)
//

#include <string>
#include <iostream>
#include <list>
#include <deque>
#include "ESTLUtil.h"
#include "Widget.h"


// C API: this function takes a pointer to an array of at most arraySize 
// doubles and writes data to it. It returns the number of doubles written.
size_t fillArray(double *pArray, size_t arraySize)
{
	size_t i;
	for (i = 0; i < arraySize; i++)
		pArray[i] = i;
	return i;
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	list<Widget> lw;

	lw.push_back(Widget(1));
	lw.push_back(Widget(2));
	lw.push_back(Widget(3));
	lw.push_back(Widget(4));

	for (list<Widget>::iterator i = lw.begin(); i != lw.end(); ++i) {
		i->redraw();
	}

	for_each(lw.begin(), lw.end(),		// see Item 41 for info 
		mem_fun_ref(&Widget::redraw));		// on mem_fun_ref


	{
		for (list<Widget>::iterator i = lw.begin(); i != lw.end(); ++i) {
			i->redraw();
		}
	}

	for_each(lw.begin(), lw.end(),		// this call evaluates
		mem_fun_ref(&Widget::redraw));		// lw.end() exactly once



	////////////////////////////////////////////////////////////////////
	const int maxNumDoubles = 10;
	
	double data[maxNumDoubles];				// create local array of 
											// max possible size

	deque<double> d;						// create deque, put
	d.push_back(2.5);						// data into it
	d.push_back(3.7);
	d.push_back(-191.5);
	d.push_back(2.2360679);

	deque<double> save_d = d;
	printContainer("deque initially: ", d);

	size_t numDoubles =
		fillArray(data, maxNumDoubles);		// get array data from API

	{
		for (size_t i = 0; i < numDoubles; ++i) {		// for each i in data, 
			d.insert(d.begin(), data[i] + 41);			// insert data[i]+41 at the
		}												// front of d; this code 
	}													// has a bug!

	printContainer("deque after inserts: ", d);

	/////////////////////////////////////////////////////////////////////////

	d = save_d;
	printContainer("\ndeque initialized again: ", d);

	{
		deque<double>::iterator insertLocation = d.begin();	// remember d's

		for (size_t i = 0; i < numDoubles; ++i) {		// insert data[i]+41
			d.insert(insertLocation++, data[i] + 41);	// at insertLocation, then
		}												// increment 
	}													// insertLocation; this 
														// code is also buggy!

	printContainer("deque after inserts, 2nd try: ", d);

	/////////////////////////////////////////////////////////////////////////

	d = save_d;
	printContainer("\ndeque initialized yet again: ", d);

	{
		deque<double>::iterator insertLocation = d.begin();	// as before

		for (size_t i = 0; i < numDoubles; ++i) {			// update insertLocation
			insertLocation =								// each time insert is
				d.insert(insertLocation, data[i] + 41);		// called to keep the 
			++insertLocation;								// iterator valid, then
		}													// increment it
	}

	printContainer("deque after inserts, 3rd try: ", d);


	d = save_d;
	printContainer("\ndeque initialized yet again: ", d);

	transform(data, data + numDoubles,				// copy all elements
			inserter(d, d.begin()),					// from data to the front
			bind2nd(plus<double>(), 41));			// of d, adding 41 to each

	printContainer("deque after transform: ", d);


	return 0;
}
