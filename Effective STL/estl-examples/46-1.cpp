//
// Example from Item 46
//
// Fails under MSVC/native lib (mem_fun_ref problem), Borland, g++
//

#include <iostream>
#include <vector>
#include <set>
using namespace std;

#include "ESTLUtil.h"

double data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(double);

inline
bool doubleGreater(double d1, double d2)
{ 	return d1 > d2; }


struct StringSize: 	
	public unary_function<string, string::size_type> {			// see Item 40

	string::size_type operator()(const string& s) const
	{ return s.size(); }

};

/*
// May not compile on some compilers:

template<typename FPType>						// return the average
FPType average(FPType val1, FPType val2)		// of 2 floating point
{												// numbers
	return (val1 + val2) / 2;
}

template<typename InputIter1, typename InputIter2>
   void writeAverages(InputIter1 begin1,		// write the pairwise
					  InputIter1 end1,			// averages of 2
					  InputIter2 begin2,		// sequences to a
					  ostream& s)				// stream
{
	transform(
		begin1, end1, begin2, 
		ostream_iterator<typename iterator_traits<InputIter1>::value_type>(s, " "),
		average<typename iterator_traits<InputIter1>::value_type>									// error?
	);
}

*/


template<typename FPType>
struct Average:
	public binary_function<FPType, FPType, FPType> {			// see Item 40

	FPType operator()(FPType val1, FPType val2) const
	{ return average(val1, val2); }

};

template<typename InputIter1, typename InputIter2>								
void writeAverages(					InputIter1 begin1, InputIter1 end1,
					InputIter2 begin2, ostream& s)		
{
	transform(
		begin1, end1, begin2, 
		ostream_iterator<typename iterator_traits<InputIter1>::value_type>(s, " "),
		Average<typename iterator_traits<InputIter1>::value_type>()
	);
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	void sort(vector<double>::iterator first, 			// beginning of range
		vector<double>::iterator last,			// end of range
		bool (*comp)(double, double))	;		// comparison function


	vector<double> v;
	v.insert(v.begin(), data, data + numValues);	// insert the data

	printContainer("after initialization, v", v);
	vector<double> save_v = v;

	sort(v.begin(), v.end(), greater<double>());
	
	printContainer("after sorting by greater<double>, v", v);

	v = save_v;
	printContainer("after re-initialization, v", v);

	sort(v.begin(), v.end(), doubleGreater);

	printContainer("after sorting by doubleGreater, v", v);

	/////////////////////////////////////////////////////////////////

	set<string> s;

	s.insert("this");
	s.insert("is");
	s.insert("a");
	s.insert("test");

	transform(s.begin(), s.end(),
		ostream_iterator<string::size_type>(cout, " "),
		mem_fun_ref(&string::size));		// won't compile with MSVC...


	cout << endl;

	transform(s.begin(), s.end(),
		ostream_iterator<string::size_type>(cout, " "),
		StringSize());


	return 0;
}
