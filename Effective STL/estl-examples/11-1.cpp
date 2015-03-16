//
// Example from ESTL Item 11
//
// Fails under MSVC/native lib.
//

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "ESTLUtil.h"
#include "Widget.h"
#include "SharedMemoryAllocator.h"
#include "SpecificHeapAllocator.h"

using namespace std;
using namespace MyLib;

void* mallocShared(size_t bytesNeeded)
{
	return 0;
}

void freeShared(void *ptr)
{}

// convenience typedef
typedef
	vector<double, SharedMemoryAllocator<double> > SharedDoubleVec;

class Heap1 {
public:
	//...
	static void* alloc(size_t numBytes, const void *memoryBlockToBeNear)
	{ return 0; }
	static void dealloc(void *ptr)
	{}
	//...
};

class Heap2 { 					// has the same alloc/dealloc interface
public:
	//...
	static void* alloc(size_t numBytes, const void *memoryBlockToBeNear)
	{  return 0; }
	static void dealloc(void *ptr)
	{}
	//...
};


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	{							// begin some block
		// ...

		SharedDoubleVec v;		// create a vector whose elements
								// are in shared memory

		// ...
	}							// end the block


	void *pVectorMemory =						// allocate enough shared
		mallocShared(sizeof(SharedDoubleVec));						// memory to hold a
												// SharedDoubleVec object

	SharedDoubleVec *pv =						// use "placement new" to 
		new (pVectorMemory) SharedDoubleVec;						// create a SharedDoubleVec
												// object in the memory;
												// see below

	//...										// use the object (via pv)

	pv->~SharedDoubleVec();						// destroy the object in the
												// shared memory

	freeShared(pVectorMemory);					// deallocate the initial
												// chunk of shared memory

	//////////////////////////////////////////////////////////

	vector<int, SpecificHeapAllocator<int, Heap1> > v;		// put both v's and
	set<int, SpecificHeapAllocator<int, Heap1> > s;			// s's elements in
															// Heap1

	list<Widget,	
			SpecificHeapAllocator<Widget, Heap2> > L;		// put both L's and

	map<int, string, less<int>,								// m's elements in
			SpecificHeapAllocator<pair<const int, string>,	// Heap2
								   Heap2> > m;

	return 0;
}
