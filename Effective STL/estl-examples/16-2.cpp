//
// More examples from Item 16
//
// Fails under MSVC/native lib (lacks range insert)
//

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <cstring>

#include "ESTLUtil.h"

double data[] = { -30.5, 102, 55.9, -19e20, 0.23, 222.2, -2.5 };
const size_t numDoubles = sizeof data / sizeof(double);

int idata[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
const size_t numValues = sizeof idata / sizeof(int);

void doSomething(const int* pInts, size_t numInts)
{
	int sum = 0;
	for (size_t i = 0; i < numInts; i++)
		sum += pInts[i];
	std::cout << "Sum of ints in the array is " << sum << std::endl;
}

// C API: this function takes a pointer to an array of at most arraySize
// doubles and writes data to it. It returns the number of doubles written,
// which is never more than arraySize.
size_t fillArray(double *pArray, size_t arraySize)
{
	size_t i, n_to_write = (arraySize > 10 ? (arraySize - 10) : 5);
	for (i = 0; i < n_to_write; i++)
		pArray[i] = i;
	return i;
}

// C API: this function takes a pointer to an array of at most arraySize
// chars and writes data to it. It returns the number of chars written,
// which is never more than arraySize.
size_t fillString(char *pArray, size_t arraySize)
{
	char chars[] = "1234567890";
	size_t i;
	for (i = 0; i < arraySize; i++)
		pArray[i] = chars[i % 10];
	return i;
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	const size_t maxNumDoubles = 15;
	const size_t maxNumChars = 15;

	vector<double> vd(maxNumDoubles);				// create a vector whose
													// size is maxNumDoubles
	cout << "after instantiation, vd.size() = " << vd.size() << endl;
	cout << "     vd.capacity() = " << vd.capacity() << endl;
	
	vd.insert(vd.begin(), data, data + numDoubles);	// insert the ints in data

	cout << "after inserting from data array, vd.size() = " << vd.size();
	cout << ", vd.capacity() = " << vd.capacity() << endl;

	size_t n;
	vd.resize(n = fillArray(&vd[0], vd.size()));	// have fillArray write data
													// into vd, then resize vd
													// to the number of
													// elements fillArray wrote
	cout << "fillArray returned: " << n << endl;
	printContainer("after resizing, vd", vd);
	cout << "    vd.size() = " << vd.size() << ", vd.capacity() = " << vd.capacity() << endl;

	vector<char> vc(maxNumChars);					// create a vector whose
													// size is maxNumChars
	size_t charsWritten = fillString(&vc[0], vc.size()); // have fillString write
													// into vc
	string s(vc.begin(), vc.begin()+charsWritten);	// copy data from vc to s
													// via range constructor
													// ( see Item 5)
	cout << "fillString returned: " << charsWritten << endl;
	cout << "s = " << s << endl;


	{
	vector<double> vd(maxNumDoubles);				// also as above
	vd.resize(fillArray(&vd[0], vd.size()));
	printContainer("vd",vd);

	deque<double> d(vd.begin(), vd.end());			// copy data into deque													// deque
//	deque<double> d(data, data + numDoubles);		// (alternative way)

	printContainer("d",d);
	
	list<double> l(vd.begin(), vd.end());			// copy data into list
//	list<double> l(data, data + numDoubles);		// copy data into list
	printContainer("l",l);

	set<double> s(vd.begin(), vd.end());			// copy data into set
//	set<double> s(data, data + numDoubles);			// copy data into set
	printContainer("s",s);

	set<int> intSet;								// set that will hold
													// data to pass to API
	vector<int> v(intSet.begin(), intSet.end());	// copy set data into a vector
	if (!v.empty()) doSomething(&v[0], v.size());

	}
	return 0;
}
