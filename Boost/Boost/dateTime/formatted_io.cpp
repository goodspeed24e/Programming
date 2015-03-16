/*
Any example in this chapter provided results such as 2009-Jan-07 once 
executed. Some people may actually prefer a different format to display 
the results. Boost.DateTime allows to format calendar dates and times via 
the boost::date_time::date_facet and boost::date_time::time_facet classes.
*/

//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//#include <locale> 
//
//int main() 
//{ 
//  boost::gregorian::date d(2009, 1, 7); 
//  boost::gregorian::date_facet *df = new boost::gregorian::date_facet("%A, %d %B %Y"); 
//  std::cout.imbue(std::locale(std::cout.getloc(), df)); 
//  std::cout << d << std::endl; 
//}

/*
Boost.DateTime uses the concept of locales known from the C++ standard 
introduced in a nutshell in Chapter 5, String Handling. To format a calendar
date, an object of type boost::date_time::date_facet must be created and 
installed within a locale. A string describing the new format is passed to 
the constructor of boost::date_time::date_facet. The example passes %A, %d %B %Y 
specifying that the day of the week is followed by the date with the month 
written in full: Wednesday, 07 January 2009.
*/

/*
Boost.DateTime offers numerous format flags that consist of the percent 
sign followed by a character. The documentation of Boost.DateTime contains 
a complete overview over all supported flags. For example, %A specifies the
name of the weekday.

If the user base of the application is located in Germany or German-speaking
countries, it is preferable to display both the weekday and the month in 
German rather than in English.
*/

#include <boost/date_time/gregorian/gregorian.hpp> 
#include <iostream> 
#include <locale> 
#include <string> 
#include <vector> 

int main() 
{ 
  std::locale::global(std::locale("German")); 
  std::string months[12] = { "Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember" }; 
  std::string weekdays[7] = { "Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag" }; 
  boost::gregorian::date d(2009, 1, 7); 
  boost::gregorian::date_facet *df = new boost::gregorian::date_facet("%A, %d. %B %Y"); 
  df->long_month_names(std::vector<std::string>(months, months + 12)); 
  df->long_weekday_names(std::vector<std::string>(weekdays, weekdays + 7)); 
  std::cout.imbue(std::locale(std::cout.getloc(), df)); 
  std::cout << d << std::endl; 
}

/*
The names for weekdays and months can be changed by passing vectors 
containing corresponding names to the long_month_names() and 
long_weekday_names() methods of the boost::date_time::date_facet class. 
The above example now writes Mittwoch, 07. Januar 2009 to the standard 
output stream.

Boost.DateTime is pretty flexible in regards to formatted input and output. 
Besides the output classes boost::date_time::date_facet and 
boost::date_time::time_facet, the classes boost::date_time::date_input_facet
and boost::date_time::time_input_facet are available for formatted input. 
All four classes provide many methods to configure the input and output of 
the different objects provided by Boost.DateTime. For example, it is
possible to specify how periods of type boost::gregorian::date_period are 
input and output. Due to the manifold possibilities for formatted input and
output it is essential to review the documentation of Boost.DateTime.
*/