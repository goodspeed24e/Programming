/*
	This smart pointer is one of the most utilized and has been badly missed in 
	the first version of the C++ standard. It has been added to the standard as
	part of the Technical Report 1 (TR1). If this report is supported by the 
	development environment used, the class std::shared_ptr defined in memory 
	can be used. Within the Boost C++ library, this smart pointer is named 
	boost::shared_ptr and is defined in boost/shared_ptr.hpp.

	The smart pointer boost::shared_ptr is essentially similar to boost::scoped_ptr.
	The key difference is that boost::shared_ptr is not necessarily the exclusive 
	owner of an object. The ownership can be shared with other smart pointers of
	type boost::shared_ptr. In these cases, the shared object is not released until
	the last shared pointer referencing the object is destroyed.

	Since ownership can be shared with boost::shared_ptr, copies of any shared
	pointer can be created - opposed to boost::scoped_ptr. This actually allows
	the usage of smart pointers with the standard containers - something that
	cannot be done with std::auto_ptr since it transfers its ownership when
	copied. 
*/

//#include <boost/shared_ptr.hpp> 
//#include <vector> 
//
//int main() 
//{ 
//  std::vector<boost::shared_ptr<int> > v; 
//  v.push_back(boost::shared_ptr<int>(new int(1))); 
//  v.push_back(boost::shared_ptr<int>(new int(2))); 
//}

/*
Thanks to boost::shared_ptr, it is possible to safely use dynamically 
allocated objects with the standard containers as shown in the above 
example. Since boost::shared_ptr can share the ownership of its contained
object, the copies stored by the container (as well as the additional 
copies in case the container needs to be rearranged) are equal. As 
outlined before, this is not the case with std::auto_ptr which therefore 
should never be stored within a container.
*/

/*
Similar to boost::scoped_ptr, the class boost::shared_ptr provides overloads
for the following operators: operator*(), operator->() and operator bool().
In addition, get() and reset() are available as well to retrieve and 
reinitialize the address of the contained object.
*/
//#include <boost/shared_ptr.hpp> 
//
//int main() 
//{ 
//  boost::shared_ptr<int> i1(new int(1)); 
//  boost::shared_ptr<int> i2(i1); 
//  i1.reset(new int(2)); 
//}
/*
The example defines two shared pointer i1 and i2 which both refer to the 
same object of type int. While i1 is explicitly initialized with the address
returned by the new operator, i2 is copy-constructed of i1. The address of 
the contained integer of i1 is then reinitialized by a call to reset(). 
The previously contained object however is not released since it is still 
referenced by i2. The smart pointer boost::shared_ptr actually counts the 
number of shared pointers currently referencing the same object and 
releases it only once the last shared pointer loses its scope.
*/

/*
By default, boost::shared_ptr uses the delete operator to destroy the 
contained object. However, the method of destruction can actually be 
specified as the following example illustrates:
*/
#include <boost/shared_ptr.hpp> 
#include <windows.h> 

int main() 
{ 
  boost::shared_ptr<void> h(OpenProcess(PROCESS_SET_INFORMATION, FALSE, GetCurrentProcessId()), CloseHandle); 
  SetPriorityClass(h.get(), HIGH_PRIORITY_CLASS); 
}
/*
The constructor of boost::shared_ptr takes a regular function or a function
object as the second parameter which in turn is used for destruction of the
contained object. In the given example, the Windows API function 
CloseHandle() is passed. Once the variable h loses its scope, the passed 
function is called instead of the delete operator. In order to avoid 
compiler errors, the function is required to take one parameter of type
HANDLE which is the case with CloseHandle().

This example actually behaves the same as the one illustrating the RAII 
idiom earlier in this chapter. However, instead of defining a separate class
windows_handle, the example takes advantage of the specific characteristics
of boost::shared_ptr by passing a method to the constructor which is 
automatically called once the shared pointer loses its scope.
*/
