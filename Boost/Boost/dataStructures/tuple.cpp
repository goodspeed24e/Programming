/*
The Boost.Tuple library provides a class named boost::tuple which can be 
seen as a generalized version of std::pair. While std::pair can store 
exactly two values, boost::tuple gives the user free choice.
*/

//#include <boost/tuple/tuple.hpp> 
//#include <boost/tuple/tuple_io.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  typedef boost::tuple<std::string, std::string> person; 
//  person p("Boris", "Schaeling"); 
//  std::cout << p << std::endl; 
//}

/*
To use boost::tuple, the header file boost/tuple/tuple.hpp must be included.
In order to use tuples with streams, the header file boost/tuple/tuple_io.hpp 
is required as well since dependent header files are not automatically 
included.

boost::tuple is basically used the same way std::pair is. As seen in the 
above example, two values of type std::string are stored by specifying two
template arguments accordingly.

While the definition of type person could have used std::pair as well, objects
of type boost::tuple can be written to a stream. Again, this requires to 
include the header file boost/tuple/tuple_io.hpp which provides all the 
required operators. The example displays (Boris Schaeling) accordingly.
*/

/*
The important difference between boost::tuple and std::pair is the ability 
of tuples to store a virtually unlimited number of values.
*/

//#include <boost/tuple/tuple.hpp> 
//#include <boost/tuple/tuple_io.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  typedef boost::tuple<std::string, std::string, int> person; 
//  person p("Boris", "Schaeling", 43); 
//  std::cout << p << std::endl; 
//}

/*
Just like there exists a helper function std::make_pair() for std::pair, a 
tuple can be created with the help of the boost::make_tuple() function.
*/

//#include <boost/tuple/tuple.hpp> 
//#include <boost/tuple/tuple_io.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  std::cout << boost::make_tuple("Boris", "Schaeling", 43) << std::endl; 
//} 

/*
A tuple can also contain references as shown in the following example.
*/

//#include <boost/tuple/tuple.hpp> 
//#include <boost/tuple/tuple_io.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  std::string s = "Boris"; 
//  std::cout << boost::make_tuple(boost::ref(s), "Schaeling", 43) << std::endl; 
//}

/*
While "Schaeling" and 43 are passed by value and thus stored inside the 
tuple directly, the first element is a reference to the string s. 
boost::ref() from Boost.Ref is used to create such a reference. To create a 
constant reference, boost::cref() is used, respectively.

After learning how to create tuples, element access is outlined below. 
std::pair use the properties first and second to allow access. Since a tuple
does not have a fixed number of elements, access is handled in a different 
way.
*/

//#include <boost/tuple/tuple.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  typedef boost::tuple<std::string, std::string, int> person; 
//  person p = boost::make_tuple("Boris", "Schaeling", 43); 
//  std::cout << p.get<0>() << std::endl; 
//  std::cout << boost::get<0>(p) << std::endl; 
//  std::cout << p.get<2>() << std::endl; 
//  std::cout << boost::get<2>(p) << std::endl;
//}

/*
There exists two ways of accessing values in a tuple: Either by calling the
get() member method, or by passing the tuple to the free-standing boost::get()
function. In both cases, the index of the corresponding element in the tuple
must be provided as the template argument. The example accesses the first 
element of the tuple p in both cases and thus displays Boris twice.

Specifying an invalid index will result in a compiler error since validity 
of indexes is checked at compile time to avoid run-time errors.

To modify a value inside a tuple, either the get() method or the 
free-standing boost::get() function must be used.
*/

//#include <boost/tuple/tuple.hpp> 
//#include <boost/tuple/tuple_io.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  typedef boost::tuple<std::string, std::string, int> person; 
//  person p = boost::make_tuple("Boris", "Schaeling", 43); 
//  p.get<1>() = "Becker"; 
//  std::cout << p << std::endl; 
//}

/*
Both get() and boost::get() return a reference. The example modifies the 
last name and hence displays (Boris Becker 43).
*/

/*
Boost.Tuple not only offers overloaded operators to use tuples with streams
but also defines comparison operators. In order to compare tuples, the 
boost/tuple/tuple_comparison.hpp header file must be included accordingly.
*/

//#include <boost/tuple/tuple.hpp> 
//#include <boost/tuple/tuple_comparison.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  typedef boost::tuple<std::string, std::string, int> person; 
//  person p1 = boost::make_tuple("Boris", "Schaeling", 43); 
//  person p2 = boost::make_tuple("Boris", "Becker", 43); 
//  std::cout << (p1 != p2) << std::endl; 
//}

/*
The example displays 1 since the tuples p1 and p2 are different.
*/

/*
The header file boost/tuple/tuple_comparison.hpp also contains
definitions for other comparison operators such as greater-than which 
performs a lexicographical comparison.

Boost.Tuple supports a specific form of tuples named tier. Tiers are tuples,
where all elements are of reference types. They can be constructed with the
boost::tie() function.
*/

#include <boost/tuple/tuple.hpp> 
#include <boost/tuple/tuple_io.hpp> 
#include <string> 
#include <iostream> 

int main() 
{ 
  typedef boost::tuple<std::string&, std::string&, int&> person; 

  std::string firstname = "Boris"; 
  std::string surname = "Schaeling"; 
  int shoesize = 43; 
  person p = boost::tie(firstname, surname, shoesize); 
  surname = "Becker"; 
  std::cout << p << std::endl; 
}

/*
The example creates a tier p which consists of references to the firstname,
surname and shoesize variables. By modifying the variable surname, the tier
is modified concurrently.

The above example could have been written using boost::make_tuple() and 
boost::ref() instead of boost::tie() as well.
*/

//#include <boost/tuple/tuple.hpp> 
//#include <boost/tuple/tuple_io.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  typedef boost::tuple<std::string&, std::string&, int&> person; 
//
//  std::string firstname = "Boris"; 
//  std::string surname = "Schaeling"; 
//  int shoesize = 43; 
//  person p = boost::make_tuple(boost::ref(firstname), boost::ref(surname), boost::ref(shoesize)); 
//  surname = "Becker"; 
//  std::cout << p << std::endl; 
//}

/*
boost::tie() simply shortens the syntax. This function also lends itself to 
unpacking tuples. In the following example, the individual values of the 
tuple, returned by a function, are instantly stored in variables.
*/

//#include <boost/tuple/tuple.hpp> 
//#include <string> 
//#include <iostream> 
//
//boost::tuple<std::string, int> func() 
//{ 
//  return boost::make_tuple("Error message", 2009); 
//}
//
//int main() 
//{ 
//  std::string errmsg; 
//  int errcode; 
//
//  boost::tie(errmsg, errcode) = func(); 
//  std::cout << errmsg << ": " << errcode << std::endl; 
//} 

/*
Using boost::tie(), the string "Error message" as well as the error code
2009, both returned as a tuple from func(), are instantly stored in the 
variables errmsg and errcode.
*/