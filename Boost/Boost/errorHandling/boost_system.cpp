/*
Boost.System is a small library defining four classes to identify errors. 
boost::system::error_code is the most basic class and represents operating 
system specific errors. Since operating systems typically enumerate errors, 
boost::system::error_code saves an error code in a variable of type int. 
The following example illustrates how to use this class by accessing the 
Boost.Asio library.
*/

//#include <boost/system/error_code.hpp> 
//#include <boost/asio.hpp> 
//#include <iostream> 
//#include <string> 
//
//int main() 
//{ 
//  boost::system::error_code ec; 
//  std::string hostname = boost::asio::ip::host_name(ec); 
//  std::cout << ec.value() << std::endl; 
//}

/*
Boost.Asio offers the free-standing boost::asio::ip::host_name() function 
that returns the name of the computer the application is executed on.

An object of type boost::system::error_code can be passed as the sole 
argument to boost::asio::ip::host_name(). If the underlying operating 
system function fails, this argument contains the corresponding error code.
It is also possible to call boost::asio::ip::host_name() without any 
argument in case the error code is irrelevant.

boost::asio::ip::host_name() was actually broken in Boost 1.36.0 and 
therefore serves as a perfect example. The function possibly returned an 
error code even though the underlying operating system function did actually
return the name of the computer successfully. Since the issue was resolved 
in Boost 1.37.0, boost::asio::ip::host_name() can now be used without 
concerns.

Since an error code is nothing but a numeric value, it can be displayed with
the help of the value() method. Since the error code 0 usually means that
no error has occurred, the meaning of other values depends on the operating
system and should be looked up in the manual accordingly.

Compiled on Windows XP using Visual Studio 2008, the above application 
repeatedly generated error code 14 (not enough storage available to 
complete the operation) while using Boost 1.36.0. Even though 
boost::asio::ip::host_name() successfully determined the name of the 
computer, error code 14 was reported. This behavior is actually due to a
broken implementation of boost::asio::ip::host_name().
*/

/*
Besides value(), boost::system::error_code offers the category() method. 
This method returns an object of the second class defined in Boost.System:
boost::system::category.

Error codes are simply numeric values. While operating system manufacturers
such as Microsoft are able to guarantee the uniqueness of system error 
codes, keeping error codes unique throughout all existing applications is
virtually impossible for any application developer. It would require a 
centralized database filled with error codes by all software developers to
avoid reusing the same codes for different scenarios which certainly is 
impractical. For this reason, error categories exist.
*/

/*
Error codes of type boost::system::error_code always belong to a category
that can be retrieved using the category() method. Operating system errors
are represented by the predefined object boost::system::system_category.

By calling category(), a reference to the predefined 
boost::system::system_category is returned. It allows to retrieve 
specific information about the category such as the name using the 
name() method which is system in case of the system category.
*/

//#include <boost/system/error_code.hpp> 
//#include <boost/asio.hpp> 
//#include <iostream> 
//#include <string> 
//
//int main() 
//{ 
//  boost::system::error_code ec; 
//  std::string hostname = boost::asio::ip::host_name(ec); 
//  std::cout << ec.value() << std::endl; 
//  std::cout << ec.category().name() << std::endl; 
//}

/*
Errors are uniquely identified by the error code and the error category. 
Since error codes are only required to be unique within a category, developers
should create a new category whenever they want to define error codes 
specific to an application. This allows for arbitrary error codes that do
not interfere with error codes of other developers.
*/

//#include <boost/system/error_code.hpp> 
//#include <iostream> 
//#include <string> 
//
//class application_category : 
//  public boost::system::error_category 
//{ 
//public: 
//  const char *name() const { return "application"; } 
//  std::string message(int ev) const { return "error message"; } 
//}; 
//
//application_category cat; 
//
//int main() 
//{ 
//  boost::system::error_code ec(14, cat); 
//  std::cout << ec.value() << std::endl; 
//  std::cout << ec.category().name() << std::endl; 
//}

/*
A new error category is defined by creating a class derived from boost::system::error_category
and implementing different methods as required by the interface of the new
category. At minimum, the methods name() and message() must be supplied since
they are defined as pure virtual in boost::system::error_category. For 
additional methods, the default behavior can be overridden accordingly if 
required.
*/

/*
While name() returns the name of the error category, message() is used to 
retrieve the error description for a particular error code. Unlike the 
above example, the ev parameter is usually evaluated to return a description
based on the error code.

Objects of type of the newly created error category can be used to 
initialize an error code accordingly. The example defines the error code ec 
using the new application_category category. Therefore, error code 14 is no 
longer a system error; its meaning is specified by the developer of the new 
error category instead.

boost::system::error_code contains a method named default_error_condition()
which returns an object of type boost::system::error_condition. The 
interface of boost::system::error_condition is almost identical to the one
of boost::system::error_code. The only difference is the 
default_error_condition() method which is only provided by 
boost::system::error_code.
*/

#include <boost/system/error_code.hpp> 
#include <boost/asio.hpp> 
#include <iostream> 
#include <string> 

int main() 
{ 
  boost::system::error_code ec; 
  std::string hostname = boost::asio::ip::host_name(ec); 
  boost::system::error_condition ecnd = ec.default_error_condition(); 
  std::cout << ecnd.value() << std::endl; 
  std::cout << ecnd.category().name() << std::endl; 
}

/*
boost::system::error_condition is used just like boost::system::error_code.
Both the value() and category() method can be called for the boost::system::error_condition
object as shown in the above example.

The reason for having two more or less identical classes is fairly simple: 
While boost::system::error_code is used for platform dependent error codes, 
boost::system::error_condition is used to access platform independent error
codes instead. By calling the default_error_condition() method, a platform
dependent error code is translated into a platform independent error code
of type boost::system::error_condition.

If the above application is executed, it displays the number 12 and the 
error category GENERIC. The platform dependent error code 14 has been 
translated into the platform independent error code 12. Thanks to 
boost::system::error_condition, the error is always represented by the 
same number - disregarding of the underlying platform. While Windows 
reports the error as 14, the same error may be reported as 25 with a 
different operating system. Using boost::system::error_condition, the error
will always be reported as 12.

The last class offered by Boost.System is boost::system::system_error which
is derived from std::runtime_error. It can be used to transport an error 
code of type boost::system::error_code within an exception.
*/

//#include <boost/asio.hpp> 
//#include <boost/system/system_error.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  try 
//  { 
//    std::cout << boost::asio::ip::host_name() << std::endl; 
//  } 
//  catch (boost::system::system_error &e) 
//  { 
//    boost::system::error_code ec = e.code(); 
//    std::cerr << ec.value() << std::endl; 
//    std::cerr << ec.category().name() << std::endl; 
//  } 
//}

/*
The free-standing boost::asio::ip::host_name() function is provided in two 
versions: One expecting an argument of type boost::system::error_code and 
one expecting no arguments. The second version will throw an exception of
type boost::system::system_error in case of an error. The exception 
transports the error code of type boost::system::error_code accordingly.
*/