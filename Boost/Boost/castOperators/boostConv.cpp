/*
The library Boost.Conversion consists of only two header files. 
While boost/cast.hpp defines the two cast operators boost::polymorphic_cast 
and boost::polymorphic_downcast, boost/lexical_cast.hpp offers the cast 
operator boost::lexical_cast, respectively.

The goal of boost::polymorphic_cast and boost::polymorphic_downcast is to 
embody type casts, usually done with dynamic_cast, more precisely as shown 
in the following example.
*/

//struct father 
//{ 
//  virtual ~father() { }; 
//}; 
//
//struct mother 
//{ 
//  virtual ~mother() { }; 
//}; 
//
//struct child : 
//  public father, 
//  public mother 
//{ 
//}; 
//
//void func(father *f) 
//{ 
//  child *c = dynamic_cast<child*>(f); 
//} 
//
//int main() 
//{ 
//  child *c = new child; 
//  func(c); 
//
//  father *f = new child; 
//  mother *m = dynamic_cast<mother*>(f); 
//}

/*
The example uses the cast operator dynamic_cast twice: It transforms the 
pointer pointing to a parent class to one pointing to the child class in 
func(). In main(), it transforms the pointer pointing to a parent class to 
one pointing to a different parent class. The first transformation is 
called downcast while the second one is called cross cast, respectively.
*/

/*
By using the cast operators of Boost.Conversion, a downcast can be 
distinguished from a cross cast.
*/

//#include <boost/cast.hpp> 
//
//struct father 
//{ 
//  virtual ~father() { }; 
//}; 
//
//struct mother 
//{ 
//  virtual ~mother() { }; 
//}; 
//
//struct child : 
//  public father, 
//  public mother 
//{ 
//}; 
//
//void func(father *f) 
//{ 
//  child *c = boost::polymorphic_downcast<child*>(f); 
//} 
//
//int main() 
//{ 
//  child *c = new child; 
//  func(c); 
//
//  father *f = new child; 
//  mother *m = boost::polymorphic_cast<mother*>(f); 
//}

/*
The cast operator boost::polymorphic_downcast can only be used for 
downcasts. It uses static_cast internally to perform the cast. Since 
static_cast does not dynamically check whether or not the type cast is 
valid, boost::polymorphic_downcast should only be used if the type cast is 
safe. In debug builds, boost::polymorphic_downcast actually uses 
dynamic_cast to verify the validity of the type cast using the assert() 
function. Please note that this test is only performed as long as the 
NDEBUG macro is defined which is usually the case for debug builds.
*/

/*
While downcasts are possible using boost::polymorphic_downcast, 
boost::polymorphic_cast is required for cross casts. boost::polymorphic_cast 
internally uses dynamic_cast since it is the only cast operator able to 
perform a cross cast. It still makes sense to prefer boost::polymorphic_cast 
since it will throw an exception of type std::bad_cast in case of an error. 
dynamic_cast, on the contrary, will return 0 if the type cast fails. 
Instead of manually verifying the return value, boost::polymorphic_cast 
provides an automatic way instead.
*/

/*
Both boost::polymorphic_downcast and boost::polymorphic_cast can only be 
used if pointers must be converted; otherwise, dynamic_cast must be used. 
Since boost::polymorphic_downcast is based on static_cast, it is not able 
to e.g. convert objects of a parent class to objects of a child class. It 
also does not make much sense to use boost::polymorphic_cast if types other 
than pointers should be converted as dynamic_cast throws an exception of 
type std::bad_cast in this case as well.

While the usage of boost::polymorphic_downcast and boost::polymorphic_cast 
is not really mandatory since all type casts can also be performed using 
dynamic_cast, Boost.Conversion also offers a second cast operator fairly 
beneficial in practice. Consider the following example.
*/

#include <boost/lexical_cast.hpp> 
#include <string> 
#include <iostream> 

int main() 
{ 
  std::string s = boost::lexical_cast<std::string>(169); 
  std::cout << s << std::endl; 
  double d = boost::lexical_cast<double>(s); 
  std::cout << d << std::endl; 
}

/*
The cast operator boost::lexical_cast can convert numbers of different data 
types. The example first converts the integer 169 to a string before 
converting the string to a floating-point number in a second step.

boost::lexical_cast internally uses streams to perform the conversion. 
Therefore, only types with overloaded operator<<() and operator>>() 
operators can be converted. The advantage of using boost::lexical_cast is 
that type conversions occur within one line of code without the need for 
manipulating the streams manually. Since the usage of streams for type 
conversions may not immediately become apparent, cast operators such as 
boost::lexical_cast also help to make the code more meaningful.
*/

/*
Please note that boost::lexical_cast not necessarily accesses streams; it 
can be optimized for different data types as well.

If a conversion fails, an exception of type boost::bad_lexical_cast, 
derived from std::bad_cast, is thrown.
*/

//#include <boost/lexical_cast.hpp> 
//#include <string> 
//#include <iostream> 
//
//int main() 
//{ 
//  try 
//  { 
//    int i = boost::lexical_cast<int>("abc"); 
//    std::cout << i << std::endl; 
//  } 
//  catch (boost::bad_lexical_cast &e) 
//  { 
//    std::cerr << e.what() << std::endl; 
//  } 
//}

/*
The example throws an exception since the string "abc" cannot be 
converted to a number of type int.
*/