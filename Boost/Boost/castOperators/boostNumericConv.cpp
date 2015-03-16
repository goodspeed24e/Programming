/*
The library Boost.NumericConversion can be used to convert numbers of one 
type to numbers of a different type. In C++, such a conversion can also 
take place implicitly as shown in the following example.
*/

//#include <iostream> 
//
//int main() 
//{ 
//  int i = 0x10000; 
//  short s = i; 
//  std::cout << s << std::endl; 
//}

/*
The example is compiled without any error since the type conversion from 
int to short takes place automatically. Even though the application can be 
executed, the result of the conversion cannot be predicted but rather 
depends on the actual compiler and its implementation. The number 0x10000 
in the variable i is too big to be stored in a variable of type short. Per 
the C++ standard, the result of this operation is "implementation defined".
Compiled with Visual C++ 2008, the application displays 0. The value of s 
certainly differs from the value in i.
*/

/*
To avoid these kind of errors while converting numbers, the cast operator 
boost::numeric_cast can be used.
*/

#include <boost/numeric/conversion/cast.hpp> 
#include <iostream> 

int main() 
{ 
  try 
  { 
    int i = -0x10000; 
    short s = boost::numeric_cast<short>(i); 
    std::cout << s << std::endl; 
  } 
  catch (boost::numeric::bad_numeric_cast &e) 
  { 
    std::cerr << e.what() << std::endl; 
  } 
}

/*
boost::numeric_cast is used exactly like the known C++ cast operators. The 
correct header file must certainly be included though; in this case 
boost/numeric/conversion/cast.hpp.

boost::numeric_cast executes the same conversion than C++ does implicitly. 
However, boost::numeric_cast actually verifies whether or not the 
conversion can take place without changing the value of the number to be 
converted. Given the example application, a conversion would not take 
place. Instead, an exception of type boost::numeric::bad_numeric_cast is 
thrown since 0x10000 is too big to be placed in a variable of type short.
*/

/*
Strictly speaking, an exception of type boost::numeric::positive_overflow is
thrown. This type specifies a so-called overflow - in this case for 
positive numbers. There also exists a type boost::numeric::negative_overflow 
which specifies an overflow for negative numbers instead.
*/

//#include <boost/numeric/conversion/cast.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  try 
//  { 
//    int i = -0x10000; 
//    short s = boost::numeric_cast<short>(i); 
//    std::cout << s << std::endl; 
//  } 
//  catch (boost::numeric::negative_overflow &e) 
//  { 
//    std::cerr << e.what() << std::endl; 
//  } 
//}

/*
Boost.NumericConversion defines additional exception types, all derived 
from boost::numeric::bad_numeric_cast. Since boost::numeric::bad_numeric_cast
is derived from std::bad_cast itself, a catch handler can also catch 
exceptions of this type.
*/
