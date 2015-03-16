//
// Example from ESTL Item 45
//

#include <list>
#include <iostream>
#include <vector>
#include "ESTLUtil.h"
#include "Widget.h"

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

//class Timestamp {  };
#define Timestamp Widget

bool operator<(const Timestamp& lhs,		// returns whether lhs
				const Timestamp& rhs); 		// precedes rhs in time


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	list<Widget> lw;						// list of Widgets
	for (size_t j = 0; j < 50; j++)
		lw.push_back(Widget(j));

	Widget w(5);							// special Widget value


	if (count(lw.begin(), lw.end(), w)) {
		cout << "w is in lw" << endl;		// w is in lw
	} else {
		cout << "w is NOT in lw" << endl;	// it's not
	}

	////////////////////////////////////////////////////////

	if (count(lw.begin(), lw.end(), w) != 0)
		cout << "w is in lw" << endl;		// w is in lw


	////////////////////////////////////////////////////////

	if (find(lw.begin(), lw.end(), w) != lw.end()) {
		cout << "w is in lw" << endl;		// w is in lw
	} else {
		cout << "w is NOT in lw" << endl;	// it's not
	}

	////////////////////////////////////////////////////////

	list<Widget>::iterator i = find(lw.begin(), lw.end(), w);

	if (i != lw.end()) {
		cout << "w is in lw" << endl;		// found it, i points to the first one
	} else {
		cout << "w is NOT in lw" << endl;	// didn't find it
	}


	vector<Widget> vw;						// create vector, put
	for (size_t k = 0; k < numValues; k++)	// data into it, sort the
		vw.push_back(Widget(data[k]));
	sort(vw.begin(), vw.end());				// data


	{
		Widget w(222);							// value to search for
		cout << "\nSearching vector of Widgets with binary_search..." << endl;
		if (binary_search(vw.begin(), vw.end(), w)) {
			cout << "w is in lw" << endl;		// w is in vw
		} else {
			cout << "w is NOT in lw" << endl;	// it's not
		}
	}


	////////////////////////////////////////////////////////

	{
		Widget w(222);							// value to search for
		cout << "\nSearching vector of Widgets with lower_bound..." << endl;

		vector<Widget>::iterator i = lower_bound(vw.begin(), vw.end(), w);

		if (i != vw.end() && *i == w) {			// make sure i points to an object;
											// make sure the object has the
											// correct value; this has a bug!

			cout << "Found it!" << endl;	// found the value, i points to the
											// first object with that value
		} else {
			cout << "Not found!" << endl;	// not found
		}
	}

	////////////////////////////////////////////////////////


	{
		Widget w(222);							// value to search for
		cout << "\nSearching vector of Widgets with equal_range..." << endl;

		typedef vector<Widget>::iterator VWIter;		// convenience typedefs
		typedef pair<VWIter, VWIter> VWIterPair;					

		VWIterPair p = equal_range(vw.begin(), vw.end(), w);

		if (p.first != p.second) {			// if equal_range didn't return
											// an empty range...

			cout << "Found it!" << endl;	// found it, p.first points to the 
											// first one and p.second 
											// points to one past the last
		} else {
			cout << "Not found!" << endl;	// not found, both p.first and 
											// p.second point to the 
		}									// insertion location for

											// the value searched for

		////////////////////////////////////////////////////////

		{
			VWIterPair p = equal_range(vw.begin(), vw.end(), w);

			cout << "There are " << distance(p.first, p.second) 
						<< " elements in vw equivalent to w.";
		}
	}


	vector<Timestamp> vt;						// create vector, fill it with
	for (size_t l = 0; l < numValues; l++)		// data into it, sort the
		vt.push_back(Timestamp(data[l]));
	printContainer("\n\nvt before sorting", vt);
	
												// data, sort it so that older
	sort(vt.begin(), vt.end());					// times precede newer ones
	printContainer("vt after sorting", vt);

	vector<Timestamp> save_vt = vt;

	Timestamp ageLimit(55);

	vt.erase(vt.begin(), lower_bound(vt.begin(),	// eliminate from vt all
			vt.end(),								// objects that precede
			ageLimit));								// ageLimit's value

	printContainer("vt after erasing based on lower_bound", vt);

	vt = save_vt;									// restore vt data

	printContainer("vt reset for next test", vt);

	vt.erase(vt.begin(), upper_bound(vt.begin(),	// eliminate from vt all
		vt.end(),									// objects that precede
		ageLimit));									// or are equivalent
													// to ageLimit's value
	printContainer("vt after erasing based on upper_bound", vt);

	return 0;
}
