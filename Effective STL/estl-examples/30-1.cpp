//
// Example from Item 30
//

#include <iostream>
#include <vector>
#include <list>

#include "ESTLUtil.h"

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

int transmogrify(int x)					// this function produces
{										// some new value from x
	return x * x;
}

int main()
{
	using namespace std;
	using namespace ESTLUtils;


	vector<int> values;

	values.insert(values.begin(), data, data + numValues);	// insert the ints in data
												// into v at the front
	printContainer("After initialization, values", values);

/*
	{
	vector<int> results;							// apply transmogrify to
	transform(values.begin(), values.end(), 		// each object in values,
		results.end(),								// appending the return
		transmogrify);								// values to results; this
													// code has a bug!
	printContainer("After transform, results", results);
	}
*/
	
	{
	vector<int> results;							// apply transmogrify to
	transform(values.begin(), values.end(), 		// each object in values,
		back_inserter(results),						// inserting the return
		transmogrify);								// values at the end of
													// results.
	printContainer("After transform with back_inserter, results", results);
	}
	
	{

	list<int> results;						// results is now a list

	transform(values.begin(), values.end(), // insert transform's 
			  front_inserter(results),		// results at the front of
			  transmogrify);				// results in reverse order!

	printContainer("After transform with front_inserter, results", results);
	}


	{
	list<int> results;							// same as before

	transform(values.rbegin(), values.rend(), 	// insert transform's 
		front_inserter(results),				// results at the front of
		transmogrify);							// results; preserve the 
												// relative object ordering
	printContainer("After transform with reverse front_inserter, results", results);
	}

	{
	vector<int> results;		// as before, except now
	results.push_back(50);		// results has some data
	results.push_back(100);		// in it prior to the call to
	results.push_back(3000);	// transform

	transform(values.begin(), values.end(),							// insert the
		inserter(results, results.begin() + results.size() / 2),	// results of
		transmogrify);												// the trans-
																	// mogrifica-
																	// tions at
																	// the middle
																	// of results
	printContainer("After transform with inserter, results", results);

	}

	{
	vector<int> results;

	results.reserve(results.size() + values.size());	// ensure that results has
														// the capacity for at least
														// values.size() more
														// elements

	transform(values.begin(), values.end(),							// as above,
		inserter(results, results.begin() + results.size() / 2),	// but results
		transmogrify);												// won't do 
																	// any reallo-
	printContainer("After reserve and transform, results", results);
																	// cations
	}

/*
	{
	vector<int> results;

	results.reserve(results.size() + values.size());	// as above

	transform(values.begin(), values.end(),				// write the results of
				results.end(),							// the transmogrifications
				transmogrify);							// to uninitialized memory;
														// behavior is undefined!
	}
*/

	{
	vector<int> results;
		
	results.reserve(results.size() + values.size());	// as above

	transform(values.begin(), values.end(), 		// write the results of
				back_inserter(results),				// the transmogrifications
				transmogrify);						// to the end of results,
													// avoiding reallocations
	printContainer("After reserve/transform/back_inserter, results", results);
													// during the process
	}

	{
	vector<int> results;		// as before, except now
	results.push_back(50);		// results has some data
	results.push_back(100);		// in it prior to the call to
	results.push_back(3000);	// transform

	if (results.size() < values.size()) {			// make sure results is at
		results.resize(values.size());				// least as big as values is
	}

	transform(values.begin(), values.end(),			// overwrite the first
						results.begin(),			// values.size() elements of
						transmogrify);				// results 
	printContainer("After checking for space, results", results);


	}

	{
	vector<int> results;		// as before, except now
	results.push_back(50);		// results has some data
	results.push_back(100);		// in it prior to the call to
	results.push_back(3000);	// transform

	results.clear();			// destroy all elements in
								// results

	results.reserve(values.size());							// reserve enough space

	transform(values.begin(), values.end(), 		// put transform's return
				back_inserter(results),		// values into results
				transmogrify);

	printContainer("After clear() and transform/back_inserter, results", results);
	}
	return 0;
}
