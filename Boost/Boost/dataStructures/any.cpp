/*
Strongly typed languages such as C++ require that each variable has a 
specific data type determining the nature of information it can store. To 
store arbitrary information in a variable, a language such as JavaScript 
can be used which allows storing a character string, a number and a boolean
value using the same variable. Variables in JavaScript allow storing any 
kind of information.

The library Boost.Any offers the boost::any class which, similar to 
JavaScript, offers the ability to store arbitrary information in C++.
*/

//#include <boost/any.hpp> 
//
//int main() 
//{ 
//  boost::any a = 1; 
//  a = 3.14; 
//  a = true; 
//}

/*
In order to use boost::any, the header file boost/any.hpp must be included. 
Objects of type boost::any can then be created to store arbitrary 
information.

Please note that variables of type boost::any cannot really store any kind 
of information; Boost.Any requires certain preconditions, albeit minimal 
ones. Any information, stored in a variable of type boost::any, must be 
copy constructible. Hence, to store a character string in a variable of 
type boost::any, std::string needs to be explicitly accessed as shown in 
the following example.
*/

//#include <boost/any.hpp> 
//#include <string> 
//
//int main() 
//{ 
//  boost::any a = 1; 
//  a = 3.14; 
//  a = true; 
//  a = std::string("Hello, world!"); 
//}

/*
If the application would try to assign "Hello, world!" to a directly, the 
compiler would abort with an error since character strings are arrays 
comprised of elements of type char which are not copy constructible in C++.

To access the content of variables of type boost::any, the cast operator 
boost::any_cast must be used.
*/

//#include <boost/any.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::any a = 1; 
//  std::cout << boost::any_cast<int>(a) << std::endl; 
//  a = 3.14; 
//  std::cout << boost::any_cast<double>(a) << std::endl; 
//  a = true; 
//  std::cout << boost::any_cast<bool>(a) << std::endl; 
//}

/*
By passing the corresponding data type as the template argument to 
boost::any_cast, the content of the variable is converted accordingly. In 
case an invalid data type is specified, an exception of type 
boost::bad_any_cast is thrown.
*/

//#include <boost/any.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  try 
//  { 
//    boost::any a = 1; 
//    std::cout << boost::any_cast<float>(a) << std::endl; 
//  } 
//  catch (boost::bad_any_cast &e) 
//  { 
//    std::cerr << e.what() << std::endl; 
//  } 
//}

/*
The above example throws an exception since the template argument of type
float does not match the type int stored in a. It is important to always
specify the same data type as used for the variable of type boost::any. The
application would also throw an exception if either short or long would be
specified as the template argument.

Since boost::bad_any_cast is derived from std::bad_cast, catch handlers can
catch exceptions of this type accordingly.

To check whether or not a variable of type boost::any contains information,
the empty() method is used. To check the data type of the stored information
instead, type() can be used.
*/

#include <boost/any.hpp> 
#include <typeinfo> 
#include <iostream> 

int main() 
{ 
  boost::any a = 1; 
  if (!a.empty()) 
  { 
    const std::type_info &ti = a.type(); 
    std::cout << ti.name() << std::endl; 

	int *i = boost::any_cast<int>(&a); 
	std::cout << *i << std::endl; 
  } 
}

/*
The example uses both empty() and type(). While empty() returns a boolean 
value, the return value of type() is of type std::type_info which is 
defined in typeinfo.
*/

/*
To conclude this section, the final example shows how to obtain a pointer 
to the value stored in a variable of type boost::any using boost::any_cast.
*/

//#include <boost/any.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::any a = 1; 
//  int *i = boost::any_cast<int>(&a); 
//  std::cout << *i << std::endl; 
//}

/*
All it takes is passing a pointer to the variable of type boost::any as the
argument to boost::any_cast; the template arguments remain unchanged.
*/