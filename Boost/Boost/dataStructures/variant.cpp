/*
The difference between Boost.Variant and Boost.Any is the ability of 
Boost.Variant to store a fixed number of types while Boost.Any allows to 
store one value of any type. Consider the following example.
*/

//#include <boost/variant.hpp> 
//
//int main() 
//{ 
//  boost::variant<double, char> v; 
//  v = 3.14; 
//  v = 'A'; 
//}

/*
Boost.Variant provides a class named boost::variant which is defined in 
boost/variant.hpp. Since boost::variant is a template, at least one 
argument must be specified. The one or multiple template arguments specify 
the supported data types. The example application can store values of both 
type double and char in v. In case a value of type int would be assigned to
v, the resulting code would not compile.

While the above example could have used a union as well, boost::variant 
allows to store data types such as std::string which is not possible with 
unions since they cannot contain any class member.
*/

//#include <boost/variant.hpp> 
//#include <string> 
//
//int main() 
//{ 
//  boost::variant<double, char, std::string> v; 
//  v = 3.14; 
//  v = 'A'; 
//  v = "Hello, world!"; 
//}

/*
To display the stored values of v, the free-standing boost::get() function
is used.
*/

//#include <boost/variant.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::variant<double, char, std::string> v; 
//  v = 3.14; 
//  std::cout << boost::get<double>(v) << std::endl; 
//  v = 'A'; 
//  std::cout << boost::get<char>(v) << std::endl; 
//  v = "Hello, world!"; 
//  std::cout << boost::get<std::string>(v) << std::endl; 
//}

/*
boost::get() expects one of the valid data types for the corresponding
variable as its template argument. Specifying an invalid type results in a
run-time error since validation of data types does not take place during
compilation.
*/

/*
Variables of type boost::variant can be written to streams such as the 
standard output stream directly, bypassing the hazard of run-time errors.
*/

//#include <boost/variant.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::variant<double, char, std::string> v; 
//  v = 3.14; 
//  std::cout << v << std::endl; 
//  v = 'A'; 
//  std::cout << v << std::endl; 
//  v = "Hello, world!"; 
//  std::cout << v << std::endl; 
//}

/*
To process values differently, Boost.Variant provides a function named 
boost::apply_visitor().
*/

//#include <boost/variant.hpp> 
//#include <boost/any.hpp> 
//#include <vector> 
//#include <string> 
//#include <iostream> 
//
//std::vector<boost::any> vector; 
//
//struct output : 
//  public boost::static_visitor<> 
//{ 
//  void operator()(double &d) const 
//  { 
//    vector.push_back(d); 
//  } 
//
//  void operator()(char &c) const 
//  { 
//    vector.push_back(c); 
//  } 
//
//  void operator()(std::string &s) const 
//  { 
//    vector.push_back(s); 
//  } 
//}; 
//
//int main() 
//{ 
//  boost::variant<double, char, std::string> v; 
//  v = 3.14; 
//  boost::apply_visitor(output(), v); 
//  v = 'A'; 
//  boost::apply_visitor(output(), v); 
//  v = "Hello, world!"; 
//  boost::apply_visitor(output(), v); 
//}

/*
As its first argument, boost::apply_visitor() expects an object of a class
type derived from boost::static_visitor. This class must overload the
operator()() operator for every data type used in the variable of type
boost::variant it acts on. Consequently, the operator is overloaded three
times in the example since v supports the data types double, char and 
std::string.

Looking closely at the code, it can be noticed that boost::static_visitor 
is a template. The type of the return value for the overloaded operator()()
operator must therefore be specified as a template argument. If the 
operators do not have a return value, a template argument is not required 
as seen in the example.

The second argument passed to boost::apply_visitor() is a variable of type
boost::variant.

When used, boost::apply_visitor() automatically calls the overloaded 
operator()() operator of the first argument that matches the data type
passed in the second argument. The example application uses a different
overloaded operator every time boost::apply_visitor() is invoked - first the
one for double, followed by the one for char and finally the one for 
std::string.

The advantage of boost::apply_visitor() is not only calling the correct 
operator automatically. In addition, boost::apply_visitor() ensures that 
overloaded operators have been provided for every data type supported in 
variables of type boost::variant. If the example would have forgotten one 
of the three methods, the code would have not been compiled.

If overloaded operators are equal in functionality, the code can be 
simplified by using templates.
*/

#include <boost/variant.hpp> 
#include <boost/any.hpp> 
#include <vector> 
#include <string> 
#include <iostream> 

std::vector<boost::any> vector; 

struct output : 
  public boost::static_visitor<> 
{ 
  template <typename T> 
  void operator()(T &t) const 
  { 
    vector.push_back(t); 
  } 
}; 

int main() 
{ 
  boost::variant<double, char, std::string> v; 
  v = 3.14; 
  boost::apply_visitor(output(), v); 
  v = 'A'; 
  boost::apply_visitor(output(), v); 
  v = "Hello, world!"; 
  boost::apply_visitor(output(), v); 
}

/*
Since boost::apply_visitor() ensures code correctness at compile time, it
should be preferred to boost::get().
*/