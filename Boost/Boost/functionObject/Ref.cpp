/*
The library Boost.Ref is typically used in conjunction with Boost.Bind and 
thus is presented next. It provides two functions - 
boost::ref() and boost::cref() - defined in boost/ref.hpp.

Boost.Ref is of importance whenever functions containing at least one 
reference parameter should be used with boost::bind(). 
Since boost::bind() copies its parameters, references need to be handled 
separately.
*/
#include <boost/bind.hpp> 
#include <iostream> 
#include <vector> 
#include <algorithm> 

void add(int i, int j, std::ostream &os) 
{ 
  os << i + j << std::endl; 
} 

int main() 
{ 
  std::vector<int> v; 
  v.push_back(1); 
  v.push_back(3); 
  v.push_back(2); 

  std::for_each(v.begin(), v.end(), boost::bind(add, 10, _1, boost::ref(std::cout))); 
}

/*
The above example uses the known add() function from the previous paragraph.
This time however, the function expects a reference to a stream object in 
order to print the information. Since parameters to boost::bind() are 
passed by value, std::cout cannot be used directly since otherwise the 
function would attempt to create a copy of it.

Using the template function boost::ref(), streams such as std::cout can be 
passed by reference which allows to compile the example successfully.

In order to pass constant objects by reference, the template function 
boost::cref() can be used instead.
*/
