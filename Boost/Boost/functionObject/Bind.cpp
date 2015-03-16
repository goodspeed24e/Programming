/*
Boost.Bind is a library simplifying a mechanism already provided by the C++
standard using the std::bind1st() and std::bind2nd() 
template functions: The usage of functions with a virtually
unlimited number of parameters in scenarios expecting 
functions with a specific signature. One of the best 
examples for such a scenario is the many different 
algorithms defined by the C++ standard.
*/

//#include <iostream> 
//#include <vector> 
//#include <algorithm> 
//
//void print(int i) 
//{ 
//  std::cout << i << std::endl; 
//} 
//
//int main() 
//{ 
//  std::vector<int> v; 
//  v.push_back(1); 
//  v.push_back(3); 
//  v.push_back(2); 
//
//  std::for_each(v.begin(), v.end(), print); 
//}

/*
For its third parameter, the algorithm std::for_each() expects a function or
function object taking exactly one parameter. If std::for_each() is 
executed, all elements of the particular container - in the above example 
of type int - are sequentially passed to the print() function. However, if
a function with a different signature should be used, things are getting 
complicated. For example, imagine if the following function add(), adding up
a constant value to each element of the container and displaying the result,
should be passed instead.
*/

//void add(int i, int j) 
//{ 
//  std::cout << i + j << std::endl; 
//} 

/*
Since std::for_each() expects a function taking one parameter only, the 
add() function cannot be passed directly. Instead, the source code needs 
to be modified.
*/

//#include <iostream> 
//#include <vector> 
//#include <algorithm> 
//#include <functional> 
//
//class add 
//  : public std::binary_function<int, int, void> 
//{ 
//public: 
//  void operator()(int i, int j) const 
//  { 
//    std::cout << i + j << std::endl; 
//  } 
//}; 
//
//int main() 
//{ 
//  std::vector<int> v; 
//  v.push_back(1); 
//  v.push_back(3); 
//  v.push_back(2); 
//
//  std::for_each(v.begin(), v.end(), std::bind1st(add(), 10)); 
//} 

/*
The above application adds up the value 10 to every element of the 
container v and displays the result using the standard output stream.

The source code had to be substantially modified in order to allow for this
though: The add() function has been converted to a function object derived
from std::binary_function.

Boost.Bind simplifies the binding between different functions. It consists 
of the boost::bind() template function only and is defined in boost/bind.hpp.
This function allows to implement the above example as follows:
*/

//#include <boost/bind.hpp> 
//#include <iostream> 
//#include <vector> 
//#include <algorithm> 
//
//void add(int i, int j) 
//{ 
//  std::cout << i + j << std::endl; 
//} 
//
//int main() 
//{ 
//  std::vector<int> v; 
//  v.push_back(1); 
//  v.push_back(3); 
//  v.push_back(2); 
//
//  std::for_each(v.begin(), v.end(), boost::bind(add, 10, _1)); 
//}

/*
Functions like add() do not need to be converted to a function object any
longer in order to be used with std::for_each(). Using boost::bind(), the
function can be used as is by passing it as the first parameter.

Since the add() function expects two parameters, they need to be passed to
boost::bind() as well. The first one is the constant value 10, the second
one is a weird looking _1.

_1 is called a placeholder and is defined in Boost.Bind. Besides _1, 
Boost.Bind also defines _2 and _3. Using these placeholders, boost::bind()
can be transformed into an unary, binary or tertiary function. In the case
of _1, boost::bind() is transformed into an unary function - a function 
expecting a single parameter. This is necessary since std::for_each() 
expects such an unary function as its third parameter.

Once the application is executed, std::for_each() calls the unary function
for each element of the container v. The element value is passed to the 
unary function using the placeholder _1. The placeholder as well as the 
constant value are being further passed to the add() function. Using this
mechanism, std::for_each() only sees the unary function defined by 
boost::bind(). boost::bind() itself simply calls a different function and 
passes items such as a constant value or placeholders as parameters.
*/

/*
The following example defines a binary function by means of boost::bind() 
which is utilized with the std::sort() algorithm which expects a binary 
function as its third parameter.
*/

//#include <boost/bind.hpp> 
//#include <vector> 
//#include <algorithm> 
//
//bool compare(int i, int j) 
//{ 
//  return i > j; 
//} 
//
//int main() 
//{ 
//  std::vector<int> v; 
//  v.push_back(1); 
//  v.push_back(3); 
//  v.push_back(2); 
//
//  std::sort(v.begin(), v.end(), boost::bind(compare, _1, _2)); 
//}

/*
Due to the usage of the two placeholders _1 and _2, boost::bind() defines a
binary function. The std::sort() algorithm calls this function with two 
elements from the container v and uses the return value to sort the 
container accordingly. Based on the definition of the compare() function, 
the container is sorted in descending order.

However, since compare() already is a binary function, the usage of 
boost::bind() is actually superfluous.
*/

//#include <boost/bind.hpp> 
//#include <vector> 
//#include <algorithm> 
//
//bool compare(int i, int j) 
//{ 
//  return i > j; 
//} 
//
//int main() 
//{ 
//  std::vector<int> v; 
//  v.push_back(1); 
//  v.push_back(3); 
//  v.push_back(2); 
//
//  std::sort(v.begin(), v.end(), compare); 
//}

/*
The usage of boost::bind() can still make sense though. For example, in 
case the container should be sorted in ascending order without changing
the definition of the compare() function.
*/

#include <boost/bind.hpp> 
#include <vector> 
#include <algorithm> 

bool compare(int i, int j) 
{ 
  return i > j; 
} 

int main() 
{ 
  std::vector<int> v; 
  v.push_back(1); 
  v.push_back(3); 
  v.push_back(2); 

  std::sort(v.begin(), v.end(), boost::bind(compare, _2, _1)); 
}

/*
This example only changed the order of the placeholders: _2 is passed as
the first parameter while _1 is passed as the second parameter to compare()
which effectively changes the sorting order.
*/