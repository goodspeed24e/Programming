//
// More from ESTL Item 22
//

#include <iostream>
#include <string>
#include <set>
#include <map>
#include "ESTLUtil.h"
using namespace std;

class Employee {
public:
	//...
	//	const string& name() const {};			// get employee name
	void setName(const string& name) {};		// set employee name

	//	const string& title() const {};			// get employee title
	void setTitle(const string& title) {};		// set employee title

	int idNumber() const {return 0;}			// get employee ID number
	//...
};


struct IDNumberLess:
	public binary_function<Employee, Employee, bool> {			// see Item 40
	bool operator()(				const Employee& lhs,
					const Employee& rhs) const
	{ return lhs.idNumber() < rhs.idNumber(); }
};

typedef set<Employee, IDNumberLess> EmpIDSet;




int main()
{
	using namespace std;
	using namespace ESTLUtils;

	map<int, string> m;
	typedef map<int, string>::value_type mtype;
	
	m.insert(mtype(10, string("hello")));
	m.insert(mtype(20, string("goodbye")));

    //	show(m);
	
//	m.begin()->first = 10;		// error! map keys can't be changed

	multimap<int, string> mm;

	m.insert(mtype(30, string("hello again")));
	m.insert(mtype(40, string("goodbye again")));
	m.insert(mtype(40, string("goodbye again")));

//	mm.begin()->first = 20;		// error! mulitmap keys can't 
								// be changed, either

	////////////////////////////////////////////////////////////////

EmpIDSet se;			// as before, se is a set of employees
						// sorted by ID number
Employee selectedID;	// as before, selectedID is a dummy
						// employee with the selected ID
						// number

EmpIDSet::iterator i = se.find(selectedID);
//  if (i != se.end()) {
//  	i->setTitle("Corporate Deity");							// some STLs will reject this
//  }															// line because *i is const

if (i != se.end()) {											// cast away
	const_cast<Employee&>(*i).setTitle("Corporate Deity");		// constness
}																// of *i

if (i != se.end()) {											// cast *i 
	static_cast<Employee>(*i).setTitle("Corporate Deity");		// to an
}																// Employee

if (i != se.end()) {											// same as above,
	((Employee)(*i)).setTitle("Corporate Deity");				// but using C 
}																// cast syntax


	if (i != se.end()) {			
		Employee tempCopy(*i);									// copy *i into tempCopy
		tempCopy.setTitle("Corporate Deity");					// modify tempCopy
	}

    {
      EmpIDSet se;												// as before, se is a set of employees
																// sorted by ID number
      Employee selectedID;										// as before, selectedID is a dummy
																// employee with the desired ID number

      EmpIDSet::iterator i =
        se.find(selectedID);									// Step 1: find element to change
      if (i != se.end()) {
        Employee e(*i);											// Step 2: copy the element
        e.setTitle("Corporate Deity");							// Step 3 (formerly 4): modify the copy
        se.erase(i++);											// Step 4 (formerly 3): remove the element;
																// increment the iterator to maintain
																// its validity (see Item 9)
        se.insert(i, e);										// Step 5: insert new value; hint that its
																// location is the same as that of the 
      }															// original element

    }

	return 0;
}
