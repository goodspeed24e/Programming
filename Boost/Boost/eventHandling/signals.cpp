/*
While the name of the library seems to be a bit misleading at first, it 
actually is not. Boost.Signals implements a pattern named signal to slot 
which is based on the concept that associated slots are executed once the
corresponding signal is issued. In principle, one can substitute the 
words 'signal' and 'slot' with 'event' and 'event handler', respectively.

However, since signals can be issued at any given time, the concept renounces events.

Consequently, Boost.Signals does not offer classes that resemble events.
Instead, it provides a class named boost::signal defined in boost/signal.hpp. 
This header file is actually the only one required knowing since it will 
include dependent header files automatically.

Boost.Signals defines additional classes residing in the boost::signals 
namespace. Since boost::signal is the most commonly used class, it actually
resides in the namespace boost instead.
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//
//void func() 
//{ 
//  std::cout << "Hello, world!" << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::signal<void ()> s; 
//  s.connect(func); 
//  s(); 
//}

/*
boost::signal is actually implemented as a template function expecting the
signature of a function, used as the event handler, as its template 
parameter. In the example, only functions with a signature of void () can 
be associated with the signal s successfully.

The function func() is associated with the signal s using the connect()
method. Since func() conforms to the required void () signature, the 
association is successfully established. func() is therefore called 
whenever the signal s is triggered.

The signal is triggered by calling s just like a regular function. The 
signature of this function corresponds to the one passed as the template 
parameter: The brackets are empty since void () does not expect any 
parameters.

Calling s results in a trigger which in turn executes the func() function 
- previously associated using connect() - accordingly.

The same example can also be realized using Boost.Function instead.
*/

//#include <boost/function.hpp> 
//#include <iostream> 
//
//void func() 
//{ 
//  std::cout << "Hello, world!" << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::function<void ()> f; 
//  f = func; 
//  f(); 
//} 

/*
Similar to the previous example, func() is associated with f. Once called,
func() is executed accordingly. While Boost.Function is limited to these
scenarios, Boost.Signals offers far more variety such as associating
multiple functions with a particular signal as shown in the following
example.
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//
//void func1() 
//{ 
//  std::cout << "Hello" << std::flush; 
//} 
//
//void func2() 
//{ 
//  std::cout << ", world!" << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::signal<void ()> s; 
//  s.connect(func1); 
//  s.connect(func2); 
//  s(); 
//}

/*
boost::signal allows assigning multiple functions to a particular signal by
calling the connect() method repeatedly. Whenever the signal is triggered,
the functions are executed in the order they have been previously associated
using connect().

Alternatively, the order can be explicitly specified using an overloaded 
version of the connect() method that expects a value of type int as an 
additional parameter.
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//
//void func1() 
//{ 
//  std::cout << "Hello" << std::flush; 
//} 
//
//void func2() 
//{ 
//  std::cout << ", world!" << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::signal<void ()> s; 
//  s.connect(1, func2); 
//  s.connect(0, func1); 
//  s(); 
//}

/*
As with the previous example, func1() is executed before func2().

To release an associated function with a given signal, the disconnect() 
method is used.
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//
//void func1() 
//{ 
//  std::cout << "Hello" << std::endl; 
//} 
//
//void func2() 
//{ 
//  std::cout << ", world!" << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::signal<void ()> s; 
//  s.connect(func1); 
//  s.connect(func2); 
//  s.disconnect(func2); 
//  s(); 
//}

/*
This example only prints Hello since the association with func2() has been
released prior to triggering the signal.

Besides connect() and disconnect(), boost::signal offers only a few 
additional methods.
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//
//void func1() 
//{ 
//  std::cout << "Hello" << std::flush; 
//} 
//
//void func2() 
//{ 
//  std::cout << ", world!" << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::signal<void ()> s;
//  s.connect(func1); 
//  s.connect(func2); 
//  std::cout << s.num_slots() << std::endl; 
//  if (!s.empty()) 
//    s(); 
//  s.disconnect_all_slots(); 
//}

/*
num_slots() returns the number of associated functions. If no function is 
associated, num_slots() returns 0 accordingly. In this particular case, the
empty() method can be used instead. The disconnect_all_slots() method 
actually does exactly what its name expresses: It releases all existing
associations.

After seeing how functions are associated with signals as well as 
understanding what happens once a signal is triggered, one question 
actually remains: What happens to the return values of these functions? 
The following example answers this question.
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//
//int func1() 
//{ 
//  return 1; 
//} 
//
//int func2() 
//{ 
//  return 2; 
//} 
//
//int main() 
//{ 
//  boost::signal<int ()> s; 
//  s.connect(func1); 
//  s.connect(func2); 
//  std::cout << s() << std::endl; 
//}

/*
Both func1() and func2() now have a return value of type int. s processes 
both return values and writes them to the standard output stream somehow.
However, what happens exactly?

The above example will actually write 2 to the standard output stream. Both
return values were correctly accepted by s but were ignored except for the
last one. By default, only the last return value of all associated functions
is actually returned.

It is possible to customize a signal so that the individual return values
are processed accordingly. For that purpose, a so-called combiner must be
passed to boost::signal as the second parameter.
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//#include <algorithm> 
//
//int func1() 
//{ 
//  return 1; 
//} 
//
//int func2() 
//{ 
//  return 2; 
//} 
//
//template <typename T> 
//struct min_element 
//{ 
//  typedef T result_type; 
//
//  template <typename InputIterator> 
//  T operator()(InputIterator first, InputIterator last) const 
//  { 
//    return *std::min_element(first, last); 
//  } 
//}; 
//
//int main() 
//{ 
//  boost::signal<int (), min_element<int> > s; 
//  s.connect(func1); 
//  s.connect(func2); 
//  std::cout << s() << std::endl; 
//} 

/*
A combiner is a class overloading the operator()() operator. This operator
is automatically called with two iterators pointing to all return values
for a particular signal. The example uses the standard C++ algorithm 
std::min_element() to determine and return the smallest value.

Unfortunately, it is not possible to pass an algorithm such as 
std::min_element() directly to boost::signal as a template parameter.
boost::signal expects that the combiner defines a type called result_type
that denotes the type of the value returned by the operator()() operator.
Since this type is omitted by the standard C++ algorithms, an error is 
issued during compilation accordingly.

Instead analyzing return values, a combiner can also save them.
*/

#include <boost/signal.hpp> 
#include <iostream> 
#include <vector> 
#include <algorithm> 

int func1() 
{ 
  return 1; 
} 

int func2() 
{ 
  return 2; 
} 

template <typename T> 
struct min_element 
{ 
  typedef T result_type; 

  template <typename InputIterator> 
  T operator()(InputIterator first, InputIterator last) const 
  { 
    return T(first, last); 
  } 
}; 

int main() 
{ 
  boost::signal<int (), min_element<std::vector<int> > > s; 
  s.connect(func1); 
  s.connect(func2); 
  std::vector<int> v = s(); 
  std::cout << *std::min_element(v.begin(), v.end()) << std::endl; 
} 

/*
The example saves all the return values in a vector which in turn is 
returned by s().
*/