//
// Example from Item 27
//

#include <iostream>
#include <deque>

#include "ESTLUtil.h"

int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const int numValues = sizeof data / sizeof(int);

int main()
{
	using namespace std;
	using namespace ESTLUtils;


	typedef deque<int> IntDeque;						// convenience typedefs
	typedef IntDeque::iterator Iter;
	typedef IntDeque::const_iterator ConstIter;


	IntDeque d;

	ConstIter ci(d.begin());						// ci is a const_iterator


//	Iter i(ci);										// error! no implicit conversion from 
													// const_iterator to iterator

//	Iter i(const_cast<Iter>(ci));					// still an error! can't cast a 
													// const_iterator to an iterator

	Iter i(d.begin());								// initialize i to d.begin()

/*
	advance(i, distance(i, ci));					// move i up to where ci is
													// (but see below for why this must
													// be tweaked before it will compile)
*/

	advance(i, distance<ConstIter>(i, ci));			// figure the distance between
													// i and ci (as const_iterators),
													// then move i that distance

	return 0;
}
