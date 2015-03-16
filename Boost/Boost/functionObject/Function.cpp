/*
For encapsulating function pointers, Boost.Function provides a class named 
boost::function. It is defined in boost/function.hpp and is used as follows:
*/

//#include <boost/function.hpp> 
//#include <iostream> 
//#include <cstdlib> 
//#include <cstring> 
//
//int main() 
//{ 
//  boost::function<int (const char*)> f = std::atoi; 
//  std::cout << f("1609") << std::endl; 
//  f = std::strlen; 
//  std::cout << f("1609") << std::endl; 
//}

/*
boost::function allows to define a pointer to a function with a specific 
signature. The above example defines a pointer f that can point to functions
expecting a parameter of type const char* and returning a value of type int.
Once defined, functions with matching signatures can then be assigned to the
pointer accordingly. The example program first assigns the std::atoi() 
function to f before it is reassigned to std::strlen().

Note though that the given data types do not necessarily need to match 
exactly: Even though std::strlen() uses std::size_t as its return type, 
it still can be assigned to f.

Since f is a function pointer, the assigned function can be called using the
overloaded operator()() operator. Depending on what function is currently
assigned, either std::atoi() or std::strlen() is called in the given example.

If f is called without having a function assigned, a boost::bad_function_call
exception is thrown.
*/

//#include <boost/function.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  try 
//  { 
//    boost::function<int (const char*)> f; 
//    f(""); 
//  } 
//  catch (boost::bad_function_call &ex) 
//  { 
//    std::cout << ex.what() << std::endl; 
//  } 
//} 

/*
Note that assigning the value 0 to a function pointer of type 
boost::function will release any currently assigned function. Calling it 
after releasing will also result in a boost::bad_function_call exception 
being thrown. In order to check whether or not a function pointer currently
is assigned to a function, the empty() function or the operator bool() 
operator can be used.
/*

/*
Using Boost.Function, class member functions can also be assigned to objects
of type boost::function.
*/
#include <boost/function.hpp> 
#include <iostream> 

class world 
{ 
public:
  void hello(std::ostream &os) 
  { 
    os << "Hello, world!" << std::endl; 
  } 
}; 

int main() 
{ 
  boost::function<void (world*, std::ostream&)> f = &world::hello; 
  world w; 
  f(&w, boost::ref(std::cout)); 
}
/*
When calling such a function, the first parameter passed indicates the 
particular object for which the function is called. Therefore, the first
parameter after the open parenthesis inside the template definition must
be a pointer to that particular class. The following parameters then denote
the signature of the corresponding member function.

The application also utilizes boost::ref() from the Boost.Ref library which
provides an easy mechanism of passing references to Boost.Function.
*/