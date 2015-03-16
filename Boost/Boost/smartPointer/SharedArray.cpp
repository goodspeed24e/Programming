/*
A shared array works essentially the same as a shared pointer. The crucial
difference is that the destructor of the shared array uses the delete[] 
operator by default to release the contained object. Since this operator 
only applies to array objects, a shared array must be initialized with the 
address of a dynamically allocated array.

The corresponding class for shared arrays is boost::shared_array and is 
defined in boost/shared_array.hpp.
*/
#include <boost/shared_array.hpp> 
#include <iostream> 

int main() 
{ 
  boost::shared_array<int> i1(new int[2]); 
  boost::shared_array<int> i2(i1); 
  i1[0] = 1; 
  std::cout << i2[0] << std::endl; 
}

/*
Just like with a shared pointer, the ownership of the contained object can 
be shared with other shared arrays. The example defines two variables i1 
and i2 which both refer to the same dynamically allocated array. The value
1 - stored using the operator[]() of i1 - can be referenced and e.g. printed
to the standard output stream using i2.

As with all the smart pointers introduced in this chapter, boost::shared_array
also provides the methods get() and reset(). 

In addition, the operator bool() is overloaded as well.
*/
