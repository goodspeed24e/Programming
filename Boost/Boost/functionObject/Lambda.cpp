/*
Unnamed functions - called lambda functions - currently do exist in various
programming languages but C++. With the help of the Boost.Lambda library 
however, they can now be used in C++ applications as well.

The general goal of lambda functions is to make the source code more compact
and thus more comprehensible. Take the code sample from the first paragraph
of this chapter for example.
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
This program takes the elements of the container v and writes them to the 
standard output stream using the print() function. Since print() only 
writes a simple int, the implementation of the function is fairly simple. 
Strictly speaking, it is so simple that it would be convenient if one could
simply define it within the std::for_each() algorithm directly; thus saving
the need for an additional function. The additional benefit is a more 
compact code since the algorithm and the function for the data output are
not locally separated. Boost.Lambda actually makes this a reality.
*/

//#include <boost/lambda/lambda.hpp> 
//#include <iostream> 
//#include <vector> 
//#include <algorithm> 
//
//int main() 
//{ 
//  std::vector<int> v; 
//  v.push_back(1); 
//  v.push_back(3); 
//  v.push_back(2); 
//
//  std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n"); 
//}

/*
Boost.Lambda provides several constructs to define unnamed functions. Code
is placed where executed thus skipping the overhead of enclosing it in a
function and the corresponding function call. As with the original example,
the program writes all elements of the container v to the standard output
stream.

Similar to Boost.Bind, Boost.Lambda also defines three placeholders named 
_1, _2 and _3. Unlike Boost.Bind, these placeholders are defined in a 
separate namespace though. Hence, the first placeholder in the example is 
referenced via boost::lambda::_1. In order to satisfy the compiler, the 
corresponding header file boost/lambda/lambda.hpp needs to be included.
*/

/*
Even though the position of the code being the third parameter to 
std::for_each() seems odd, Boost.Lambda allows for writing regular C++ code.
Using the placeholder, the elements of the container f can be passed to
std::cout via << in order to write them to the standard output stream.

While Boost.Lambda is quite powerful, there are some drawbacks. 
To insert a line break into the output of the above example, "\n" must 
be used instead of std::endl in order to successfully compile. 
Since the type expected by the unary std::endl template function is 
different from the one of the lambda function std::cout << boost::lambda::_1,
it cannot be used in this case.

The next revision of the C++ standard will likely add lambda functions as
an integral part to the C++ language itself thus eliminating the need for
a separate library. It may still take years though before the next revision
is published and widely adopted by the different compiler manufacturers. 
Until then, Boost.Lambda proves to be a perfect replacement as can be seen
in the following example which only writes elements greater than 1 to the
standard output stream.
*/
#include <boost/lambda/lambda.hpp> 
#include <boost/lambda/if.hpp> 
#include <iostream> 
#include <vector> 
#include <algorithm> 

int main() 
{ 
  std::vector<int> v; 
  v.push_back(1); 
  v.push_back(3); 
  v.push_back(2); 

  std::for_each(v.begin(), v.end(), 
    boost::lambda::if_then(boost::lambda::_1 > 1, 
    std::cout << boost::lambda::_1 << "\n")); 
}
/*
The header file boost/lambda/if.hpp defines several constructs to allow 
if statements within lambda functions. The most basic construct is the
boost::lambda::if_then() template function that expects two parameters: 
The first parameter evaluates a condition - if true, the second parameter 
is executed. Each parameter can be a lambda function itself as shown in the
example.

Besides boost::lambda::if_then(), Boost.Lambda provides the boost::lambda::if_then_else()
and boost::lambda::if_then_else_return() template functions - each expecting
three parameters. Additional template functions for loops, cast operators
and even for throw - allowing lambda functions to throw exceptions - are 
provided as well.

Even though complex lambda functions in C++ can be built utilizing these 
template functions, one has to consider aspects such as readability as well
as maintainability. Since one needs to learn and understand additional 
functions like boost::lambda::if_then() instead of using the known C++ 
keywords if and else, the benefit of lambda functions usually decreases 
with their complexity. Most of the time, it is more reasonable to define
a discrete function using the familiar C++ constructs instead.
*/