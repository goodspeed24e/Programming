/* A scoped array is used just like a scoped pointer. 
 The crucial difference is that the destructor of the 
 scoped array uses the delete[] operator to release 
 the contained object. Since this operator only applies
 to array objects, a scoped array must be initialized 
 with the address of a dynamically allocated array.

 The corresponding class for scoped arrays is boost::scoped_array
 and is defined in boost/scoped_array.hpp.
*/

#include <boost/scoped_array.hpp> 

int main() 
{ 
  boost::scoped_array<int> i(new int[2]); 
  *i.get() = 1; 
  i[1] = 2; 

  for (int cnt = 0 ; cnt < 2; cnt ++)
  {
	  std::cout << cnt << ":" << i[cnt] << std::endl;
  }

  i.reset(new int[3]); 
  for (int cnt = 0 ; cnt < 3; cnt ++)
  {
	  std::cout << cnt << ":" << i[cnt] << std::endl;
  }
}

/*
 The class boost::scoped_array provides overloads for 
 the operator[]() and operator bool() operators. 
 Using operator[](), a specific element of the array 
 can be accessed - an object of type boost::scoped_array
 thus behaves exactly like the array it contains.

 Just like boost::scoped_ptr, the methods get() and 
 reset() are provided as well allowing to retrieve and
 reinitialize the address of the contained object.
*/
