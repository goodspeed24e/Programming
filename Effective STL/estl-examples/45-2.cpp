//
// More examples from ESTL Item 45
//
// Fails under MSVC/nativelib: lib fails to declare list::sort as a member template.  
//

#include <string>
#include <list>
#include <set>
#include <iostream>
#include "ESTLUtil.h"
#include "Widget.h"
using namespace std;


class Person {
public:
	Person(string name = "anonymous") : n(name) {}
	//...
	const string& name() const { return n; }
	//...
	friend ostream &operator<<(ostream &os, const Person &p);
private:
	string n;
};

ostream &operator<<(ostream &os, const Person &p)
{
	return os << p.n;
}


struct PersonNameLess: 
	public binary_function<Person, Person, bool> {					// see Item 40

	bool operator()(const Person& lhs, const Person& rhs) const
	{
		return lhs.name() < rhs.name();
	}

};


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	list<Person> lp;
	lp.push_back(Person("Me"));
	lp.push_back(Person("Scott"));
	lp.push_back(Person("Leor"));
	lp.push_back(Person("Lisa"));

	printContainer("lp before sorting", lp);

	lp.sort(PersonNameLess());						// sort lp using
													// PersonNameLess

	printContainer("lp after sorting", lp);

	Person newPerson("Raymond");

	lp.insert(upper_bound(lp.begin(),		// insert newPerson after
		lp.end(),							// the last object in lp
		newPerson,							// that precedes or is 
		PersonNameLess()),					// equivalent to
		newPerson);							// newPerson

	printContainer("lp after inserting Raymond", lp);


	///////////////////////////////////////////////////////////////

	set<Widget> s;				// create set, put data into it
	s.insert(Widget(10));
	s.insert(Widget(11));
	s.insert(Widget(12));
	s.insert(Widget(13));
	

	Widget w(12);				// w still holds the value to search for


	if (s.count(w)) {				

		cout << "Widget Found!" << endl;		// a value equivalent to w exists
	} else {
		cout << "Widget Not Found!" << endl;	// no such value exists
	}


	



	return 0;
}
