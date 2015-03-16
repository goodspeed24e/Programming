//
// Example from ESTL Item 38
//

#include <string>
#include <iostream>
#include <deque>
#include "ESTLUtil.h"
#include "Widget.h"

using namespace std;


void qsort(	void *base, size_t nmemb, size_t size,
	int (*cmpfcn)(const void*, const void*));

/*
template<class InputIterator, class Function>
Function							// note return-by-value
for_each(InputIterator first,
			InputIterator last,
			Function f);		// note pass-by-value
*/

class DoSomething:
	public unary_function<int, void> {				// Item 40 explains base class
public:
	void operator()(int x) {
		cout << "In DoSomething::operator(), x = " << x << endl;
	}

	//...

};


/*
template<typename T>
class BPFC:							// BPFC = "Big Polymorphic 
	public							// Functor Class"
		unary_function<T, void> {	// Item 40 explains this
									// base class

private:

	Widget w;						// this class has lots of data,
	int x;							// so it would be inefficient
	//...							// to pass it by value

public:
	 virtual void operator()(const T& val) const;	// this is a virtual function,
	//...											// so slicing would be bad
};
*/


template<typename T>
class BPFC;

template<typename T>						// new implemenation class
class BPFCImpl : public unary_function<T, void> {							// for modified BPFC
private:
	Widget w;								// all the data that used to
	int x;									// be in BPFC are now here
	//...	
	virtual ~BPFCImpl();					// polymorphic classes need
											// virtual destructors
	virtual void operator()(const T& val) const;

	friend class BPFC<T>;					// let BPFC access the data
};

template<typename T>
class BPFC:									// small, monomorphic
	public unary_function<T, void> {		// version of BPFC
private:
	BPFCImpl<T> *pImpl;						// this is BPFC's only data
public:
	void operator()(const T& val) const		// this is now nonvirtual;
	{ pImpl->operator()(val); }				// it forwards to BPFCImpl
	//...
};



int main()
{
	using namespace std;
	using namespace ESTLUtils;

	typedef deque<int>::iterator DequeIntIter;		// convenience typedef

	deque<int> di;
	di.push_back(1);
	di.push_back(3);
	di.push_back(10);
	di.push_back(100);

	DoSomething d;						// create a function object


	for_each<DequeIntIter,				// call for_each with type
		DoSomething&>(	di.begin(),		// parameters of DequeIntIter
		di.end(),						// and DoSomething&;
		d);								// this forces d to be 
										// passed and returned
										// by reference

	return 0;
}
