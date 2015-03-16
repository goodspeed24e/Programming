//
// Example from Item 24
//

#include <iostream>
#include <map>
#include "ESTLUtil.h"
using namespace std;

class Widget {
public:
	Widget() { value = 0; }		

	Widget(double weight) {value=weight;}			// see below for info on "explicit"

	Widget& operator=(double weight) { value=weight; return *this;}
	friend ostream& operator<<(ostream&, const Widget &);
	//...
	double value;
};

ostream&operator<<(ostream& o, const Widget &w)
{
	return o << w.value;
}



template<typename MapType,		// type of map
	typename KeyArgType,		// see below for why
	typename ValueArgType>		// KeyArgType and 
								// ValueArgType are type
								// parameters
typename MapType::iterator								
efficientAddOrUpdate(MapType& m,
			const KeyArgType& k,
			const ValueArgType& v)
{
	typename MapType::iterator lb =				// find where k is or should
		m.lower_bound(k);						// go; see page 7 for why
												// "typename" is needed
												// here 

	if (lb != m.end() &&						// if lb points to a pair
			!(m.key_comp()(k, lb->first))) {	// whose key is equiv to k...
		lb->second = v;							// update the pair's value
		return lb;								// and return an iterator
	}											// to that pair
	else {
		typedef typename MapType::value_type MVT;
		return m.insert(lb, MVT(k, v));			// add pair(k, v) to m and
	}											// return an iterator to the
}												// new map element


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	map<int, Widget> m;				

	m[1] = 1.50;
	m[2] = 3.67;
	m[3] = 10.5;
	m[4] = 45.8;
	m[5] = 0.0003;

	printContainer("after initialization, m", m);

	typedef map<int, Widget> IntWidgetMap;					// convenience
															// typedef

	pair<IntWidgetMap::iterator, bool> result = 			// create new map 
		m.insert(IntWidgetMap::value_type(1, Widget()));	// entry with key 1 
															// and a default-
															// constructed value 
															// object; see below
															// for a comment on
															// value_type

	result.first->second = 1.50;							// assign to the
															// newly-constructed
															// value object

//	m.insert(IntWidgetMap::value_type(make_pair(1, 1.50)));
//	m.insert(IntWidgetMap::value_type(1, 1.50));


	{
	int k = 3;
	Widget v(9.999);

	m[k] = v;				// use operator[]
							// to update k's
							// value to be v
	printContainer("after updating key 3 using [], m", m);
	}

	{
	int k = 3;
	Widget v(9.999);
	
	m.insert(IntWidgetMap::value_type(k, v)).first->second = v;	// use insert to 
	printContainer("after updating key 3 using insert, m", m);	// update k's
	}															// value to be v

	{
	int k = 3;
	Widget v(1.11111);
	IntWidgetMap::iterator
				affectedPair = 				// if key k isn't in map m, efficiently 
		efficientAddOrUpdate(m, k, v);		// add pair (k,v) to m; otherwise
											// efficiently update to v the value
											// associated with k. Return an 
											// iterator to the added or 
											// modified pair
	printContainer("after updating key 3 using effecintAdd etc., m", m);

	efficientAddOrUpdate(m, 10, 1.5);				
	printContainer("after updating key 10 using effecintAdd etc., m", m);

	}
	
	return 0;
}
