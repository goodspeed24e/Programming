/* 
	A scoped pointer is a pointer that is the sole owner of a dynamically 
	allocated object. The corresponding class is named boost::scoped_ptr and
	is defined in boost/scoped_ptr.hpp. Unlike std::auto_ptr, a scoped pointer
	is not able to transfer ownership of its contained object to another 
	scoped pointer. Once initialized with an address, the dynamically 
	allocated object is released during destruction.

	Since a scoped pointer simply stores and solely owns an address, the 
	implementation of boost::scoped_ptr is less complex than std::auto_ptr.
	boost::scoped_ptr should be preferred if transfer of ownership is not 
	required. In these situations, it may be a better choice than 
	std::auto_ptr to avoid inadvertent transfer of ownership.
*/

#include <boost/scoped_ptr.hpp> 

int main() 
{ 
	boost::scoped_ptr<int> i(new int); 
	std::cout << "my addr: " << i.get() << "\ninit value:" << *i.get() << std::endl;
	*i = 10; 
	std::cout << *i << std::endl;
	{
		boost::scoped_ptr<int> i(new int); 
std::cout << "my addr: " << i.get() << "\ninit value:" << *i.get() << std::endl;;
		*i = 1; 
		std::cout << *i <<std::endl;
		*i.get() = 2; 
		std::cout << *i << std::endl;
		i.reset(new int);
		std::cout << *i << std::endl;
	}
	*i.get() = 20; 
	std::cout << *i << std::endl;
	i.reset(new int);
	std::cout << *i << std::endl;
}

/*
	Once initialized, the contained object of the smart pointer boost::scoped_ptr
	can be accessed through an interface similar to an ordinary pointer. 
	This is achieved by providing the corresponding operator overloads 
	operator*(), operator->() as well as operator bool(). 
	In addition, the methods get() and reset() are available. While the 
	former one returns the address of the contained object, the latter one 
	allows to reinitialize the smart pointer with a new object. In this case,
	the contained object is automatically destroyed before the new object is
	assigned.

	The contained object is released using the delete operator within the
	destructor of boost::scoped_ptr. This puts an important restriction on 
	the types of objects boost::scoped_ptr can contain. boost:scoped_ptr is 
	not allowed to be initialized with the address of a dynamically 
	allocated array since this would require a call to the delete[] operator
	instead. In these cases, the class boost:scoped_array can be used which
	is introduced next.
*/
