/*
The Boost.Exception library offers a new exception type boost::exception 
allowing to add information to an exception after it has been thrown. It is
defined in boost/exception/exception.hpp. Since Boost.Exception spreads its
classes and functions over multiple header files, the following example 
rather accesses boost/exception/all.hpp to avoid including the header files
individually.
*/

//#include <boost/exception/all.hpp> 
//#include <boost/lexical_cast.hpp> 
//#include <boost/shared_array.hpp> 
//#include <exception> 
//#include <string> 
//#include <iostream> 
//
//typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info; 
//
//class allocation_failed : 
//  public boost::exception, 
//  public std::exception 
//{ 
//public: 
//  allocation_failed(std::size_t size) 
//    : what_("allocation of " + boost::lexical_cast<std::string>(size) + " bytes failed") 
//  { 
//  } 
//
//  virtual const char *what() const throw() 
//  { 
//    return what_.c_str(); 
//  } 
//
//private: 
//  std::string what_; 
//}; 
//
//boost::shared_array<char> allocate(std::size_t size) 
//{ 
//  if (size > 1000) 
//    throw allocation_failed(size); 
//  return boost::shared_array<char>(new char[size]); 
//} 
//
//void save_configuration_data() 
//{ 
//  try 
//  { 
//    boost::shared_array<char> a = allocate(2000); 
//    // saving configuration data ... 
//  } 
//  catch (boost::exception &e) 
//  { 
//    e << errmsg_info("saving configuration data failed"); 
//    throw; 
//  } 
//} 
//
//int main() 
//{ 
//  try 
//  { 
//    save_configuration_data(); 
//  } 
//  catch (boost::exception &e) 
//  { 
//    std::cerr << boost::diagnostic_information(e); 
//  } 
//}

/*
The example calls the function save_configuration_data() inside main() which
in turn calls the allocate() function. allocate() allocates memory dynamically;
however, it checks whether or not a certain limit is exceeded. This limit is
arbitrarily set to 1,000 bytes in the example.

If allocate() is called with a value greater than 1,000, an exception is
thrown accordingly which is the case inside the save_configuration_data() 
function. The function supposedly saves configuration data in the dynamically
allocated memory as indicated by the comment.

The purpose of the example is to actually throw the exception in order to 
demonstrate Boost.Exception. The exception, thrown by allocate(), is of type
allocation_failed and is derived from both boost::exception and 
std::exception.

Deriving from std::exception is certainly not necessary. allocation_failed 
could have also been derived from a different class hierarchy in order to 
embed it inside an existing framework. While the above example uses the 
class hierarchy defined by the C++ standard, deriving allocation_failed 
solely from boost::exception would have also been sufficient.

When throwing an exception of type allocation_failed, the size of the memory
expected to be allocated, is stored inside the exception to alleviate 
debugging of the corresponding application. If more memory is requested than
can be provided by allocate(), the root cause for the exception can be easily spotted.

If allocate() is called by only one function (in the example save_configuration_data()), 
this information is sufficient to locate the issue. However, in more complex
applications with many functions calling allocate() to dynamically allocate
memory, the information is no longer sufficient to effectively debug the
application. In these cases, it rather would help to actually know which
function tried to allocate more memory than allocate() can provide. Adding
more information to the exception in these cases would help the debugging
process tremendously.

The particular challenge is that allocate() does not have information such
as the caller name in order to add it to the exception accordingly.
*/

/*
Boost.Exception offers the following solution: Information can be added to 
an exception at all times by defining a data type based on boost::error_info
for every information that should be added to the exception.

boost::error_info is a template expecting two arguments: The first argument
is a so-called tag, uniquely identifying the newly created data type. 
Commonly, a structure with a unique name is utilized. The second argument 
refers to the data type of the information stored inside the exception.

The application defined a new data type errmsg_info, uniquely identifiable 
via the tag_errmsg structure, which stores a string of type std::string.

Inside the catch handler of save_configuration_data(), the data type 
tag_errmsg is accessed to create an object, initialized with the string 
"saving configuration data failed", to add additional information to the 
exception of type boost::exception via the operator<<() operator. The 
exception is then re-thrown accordingly.
*/

/*
The exception now not only carries the size of memory expected to be dynamically
allocated, but also the description of the error added inside the 
save_configuration_data() function. This description certainly helps while 
debugging since it now becomes clear which function tried to allocate more
memory than can be provided.

To retrieve all available information from an exception, the boost::diagnostic_information()
function can be used as seen in the example inside the catch handler of
main(). For every exception passed, boost::diagnostic_information() not only
calls the what() method but also accesses all additional information stored
inside the exception. A string of type std::string is returned that can 
e.g. be written to the standard output stream.
*/

/*
Above application compiled with Visual C++ 2008 displays the following message:

Throw in function (unknown)
Dynamic exception type: class allocation_failed
std::exception::what: allocation of 2000 bytes failed
[struct tag_errmsg *] = saving configuration data failedAs can be seen, the message contains the data type of the exception, the error message as retrieved from the what() method, and the description including the corresponding name of the structure.
*/

/*
boost::diagnostic_information() checks at run-time whether or not a given 
exception is derived from std::exception. Only if it is, the what() method 
is actually called.

The name of the function that has thrown the exception of type allocation_failed
is indicated as "unknown" in the message.

Boost.Exception provides a macro to throw an exception including not only
the name of the function but also additional information such as the file 
name and the line number.
*/

#include <boost/exception/all.hpp> 
#include <boost/lexical_cast.hpp> 
#include <boost/shared_array.hpp> 
#include <exception> 
#include <string> 
#include <iostream> 

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info; 

class allocation_failed : 
  public std::exception 
{ 
public: 
  allocation_failed(std::size_t size) 
    : what_("allocation of " + boost::lexical_cast<std::string>(size) + " bytes failed") 
  { 
  } 

  virtual const char *what() const throw() 
  { 
    return what_.c_str(); 
  } 

private: 
  std::string what_; 
}; 

boost::shared_array<char> allocate(std::size_t size) 
{ 
  if (size > 1000) 
    BOOST_THROW_EXCEPTION(allocation_failed(size)); 
  return boost::shared_array<char>(new char[size]); 
} 

void save_configuration_data() 
{ 
  try 
  { 
    boost::shared_array<char> a = allocate(2000); 
    // saving configuration data ... 
  } 
  catch (boost::exception &e) 
  { 
    e << errmsg_info("saving configuration data failed"); 
    throw; 
  } 
} 

int main() 
{ 
  try 
  { 
    save_configuration_data(); 
  } 
  catch (boost::exception &e) 
  { 
    std::cerr << boost::diagnostic_information(e); 
  } 
}

/*
By using the macro BOOST_THROW_EXCEPTION instead of throw, additional 
information such as function name, file name and line number are 
automatically added to the exception. This only works if the compiler 
supports corresponding macros though. While macros such as __FILE__ and
__LINE__ are defined by the C++ standard, there is no standardized macro for
returning the name of the current function. Since many of the compiler 
manufacturers provide such a macro, BOOST_THROW_EXCEPTION tries to identify
the underlying compiler and utilize the corresponding macro accordingly. 
Compiled with Visual C++ 2008, the above application displays the following
message:

.\main.cpp(31): Throw in function class boost::shared_array<char> __cdecl allocate(unsigned int)
Dynamic exception type: class boost::exception_detail::clone_impl<struct boost::exception_detail::error_info_injector<class allocation_failed> >
std::exception::what: allocation of 2000 bytes failed
[struct tag_errmsg *] = saving configuration data failedThe code compiles without errors even though the allocation_failed class is no longer derived from boost::exception. BOOST_THROW_EXCEPTION accesses a function named boost::enable_error_info() that dynamically identifies whether or not an exception is derived from boost::exception. If not, it automatically creates a new exception type derived both from the specified type and boost::exception. This mechanism is the reason for the above message to not display allocation_failed only.

Finally, this section concludes with an example to selectively access 
information added to an exception.
*/

//#include <boost/exception/all.hpp> 
//#include <boost/lexical_cast.hpp> 
//#include <boost/shared_array.hpp> 
//#include <exception> 
//#include <string> 
//#include <iostream> 
//
//typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info; 
//
//class allocation_failed : 
//  public std::exception 
//{ 
//public: 
//  allocation_failed(std::size_t size) 
//    : what_("allocation of " + boost::lexical_cast<std::string>(size) + " bytes failed") 
//  { 
//  } 
//
//  virtual const char *what() const throw() 
//  { 
//    return what_.c_str(); 
//  } 
//
//private: 
//  std::string what_; 
//}; 
//
//boost::shared_array<char> allocate(std::size_t size) 
//{ 
//  if (size > 1000) 
//    BOOST_THROW_EXCEPTION(allocation_failed(size)); 
//  return boost::shared_array<char>(new char[size]); 
//} 
//
//void save_configuration_data() 
//{ 
//  try 
//  { 
//    boost::shared_array<char> a = allocate(2000); 
//    // saving configuration data ... 
//  } 
//  catch (boost::exception &e) 
//  { 
//    e << errmsg_info("saving configuration data failed"); 
//    throw; 
//  } 
//} 
//
//int main() 
//{ 
//  try 
//  { 
//    save_configuration_data(); 
//  } 
//  catch (boost::exception &e) 
//  { 
//    std::cerr << *boost::get_error_info<errmsg_info>(e); 
//  } 
//}
/*
The example does not utilize boost::diagnostic_information() but rather 
uses boost::get_error_info() to directly access the error message of type 
errmsg_info. boost::get_error_info() returns a smart pointer of type 
boost::shared_ptr. In case the argument passed is not of type 
boost::exception, a null pointer is returned accordingly. If the 
BOOST_THROW_EXCEPTION macro is always used to throw an exception, it is 
guaranteed that the exception is derived from boost::exception - there is 
no need to check the returned smart pointer for null in these cases.
*/