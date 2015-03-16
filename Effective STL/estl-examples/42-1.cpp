//
// Example from ESTL Item 42
//

#include <string>
#include <iostream>
#include <set>
#include "ESTLUtil.h"

using namespace std;

class Widget {
public:
//	Widget

	size_t weight() const { return w; }
	size_t maxSpeed() const;

	friend bool operator<(const Widget& lhs, const Widget& rhs);

private:
	size_t w;
};

bool operator<(const Widget& lhs, const Widget& rhs)
{
	return lhs.weight() < rhs.weight();
}


template<>							// This is a specialization
struct std::less<Widget>:			// of std::less for Widget;
	public							// it's also a very bad idea.
	std::binary_function<Widget,
					Widget, 		// See Item 40 for info
					bool> {			// on this base class
	bool operator()(const Widget& lhs, const Widget& rhs) const
	{
		return lhs.maxSpeed() < rhs.maxSpeed();
	}

};


/*
namespace std {

	template<typename T>						// this is a spec. of std::less
	struct less< boost::shared_ptr<T> >:						// for boost::shared_ptr<T>
		public					// (boost is a namespace)
		binary_function<			boost::shared_ptr<T>,
					boost::shared_ptr<T>,		// this is the customary
					bool> {		// base class (see Item 40)

		bool operator()(				const boost::shared_ptr<T>& a,
						const boost::shared_ptr<T>& b) const
		{
			return less<T*>()(a.get(),b.get());					// shared_ptr::get returns 
		}						// the built-in pointer that's
								// in the shared_ptr object
	}; 
}
*/

struct MaxSpeedCompare:
	public binary_function<Widget, Widget, bool> {

	bool operator()(const Widget& lhs, const Widget& rhs) const
	{
		return lhs.maxSpeed() < rhs.maxSpeed();
	}

};



int main()
{
	using namespace std;
	using namespace ESTLUtils;

	multiset<Widget, MaxSpeedCompare> widgets;

	return 0;
}
