//
// ESTL item 2, "CustomerList" example
//

#include <list>
#include <iostream>
using namespace std;

class Customer {};

class CustomerList {
private:
	typedef list<Customer> CustomerContainer;
	typedef CustomerContainer::iterator CCIterator;
	CustomerContainer customers;
public:				// limit the amount of list-specific
//	...				// information visible through
};					// this interface

int main()
{
	CustomerList cl;
	
	return 0;
}
