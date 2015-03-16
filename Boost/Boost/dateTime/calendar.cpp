/*
Boost.DateTime only supports calendar dates based on the Gregorian calendar
which in general is not a problem since it is the most widely-used calendar.
If a meeting with someone from a different country is arranged for January 
5, 2010, it can be expected that there is no need to advise the person that
the date is based on the Gregorian calendar.
/*

/*
The Gregorian calendar was introduced by Pope Gregory XIII in 1582. Strictly
speaking, Boost.DateTime supports calendar dates for the years 1400 to 9999
which means that support goes back beyond the year 1582. Therefore, Boost.DateTime
can be used for any calendar date after the year 1400 when converted to the
Gregorian calendar. If older years are required, a different library must 
be used instead.
*/

/*
Classes and functions to process calendar dates are offered within the 
namespace boost::gregorian defined in boost/date_time/gregorian/gregorian.hpp.
To create a date, the boost::gregorian::date class is used.
*/

//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::gregorian::date d(2010, 1, 30); 
//  std::cout << d.year() << std::endl; 
//  std::cout << d.month() << std::endl; 
//  std::cout << d.day() << std::endl; 
//  std::cout << d.day_of_week() << std::endl; 
//  std::cout << d.end_of_month() << std::endl; 
//}

/*
boost::gregorian::date offers multiple constructors to manipulate the date 
creation. The most basic constructor takes a year, a month and a day as its 
arguments. If an invalid value is given, an exception of type boost::gregorian::bad_year,
boost::gregorian::bad_month or boost::gregorian::bad_day_of_month, all 
derived from std::out_of_range, is thrown.
*/

/*
As shown in the example, there are many methods provided to access a date. 
While methods such as year(), month() and day() access the initial values 
used for initialization, methods like day_of_week() and end_of_month() 
specifically calculate values.
*/

/*
Whilst the constructor of boost::gregorian::date takes values for the year,
month and day to set a date, calling the month() method actually displays 
Jan while calling the day_of_week() displays Sat. These are no regular 
numeric values but rather values of type boost::gregorian::date::month_type
and boost::gregorian::date::day_of_week_type, respectively. Nonetheless, 
Boost.DateTime offers comprehensive support for formatted input and output 
to adjust the above output from Jan to 1.

Please note that an invalid date is created by the default constructor of 
boost::gregorian::date. Such an invalid date can be created explicitly by 
passing boost::date_time::not_a_date_time as the single argument to the 
constructor.

Besides calling a constructor directly, an object of type boost::gregorian::date
can also be created via free-standing functions and methods of other objects.
*/

//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::gregorian::date d = boost::gregorian::day_clock::universal_day(); 
//  std::cout << d.year() << std::endl; 
//  std::cout << d.month() << std::endl; 
//  std::cout << d.day() << std::endl; 
//
//  d = boost::gregorian::date_from_iso_string("20100131"); 
//  std::cout << d.year() << std::endl; 
//  std::cout << d.month() << std::endl; 
//  std::cout << d.day() << std::endl; 
//}

/*
This example utilizes the boost::gregorian::day_clock class which is a clock
returning the current date. The universal_day() returns a UTC date that is 
independent of time zones and daylight savings. UTC is the international 
abbreviation for the universal time. boost::gregorian::day_clock also 
provides a method named local_day() which takes the local settings into 
account. To retrieve the current date within the local time zone, 
local_day() must be used.

The namespace boost::gregorian contains many additional free-standing 
functions to convert a date stored in a string to an object of type 
boost::gregorian::date. The example actually converts a date given in ISO 
8601 format via the boost::gregorian::date_from_iso_string() function. 
Other functions such as boost::gregorian::from_simple_string() and 
boost::gregorian::from_us_string() are available as well.
*/

/*
While boost::gregorian::date marks a specific point in time, 
boost::gregorian::date_duration rather denotes a duration.
*/

//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::gregorian::date d1(2008, 1, 31); 
//  boost::gregorian::date d2(2008, 8, 31); 
//  boost::gregorian::date_duration dd = d2 - d1; 
//  std::cout << dd.days() << std::endl; 
//}

/*
Since boost::gregorian::date overloads the operator-() operator, two points 
in time can be subtracted as shown above. The return value is of type 
boost::gregorian::date_duration and marks the duration between the two dates.

The most important method offered by boost::gregorian::date_duration is 
days() which returns the number of days the duration consists of.
*/

/*
Objects of type boost::gregorian::date_duration can also be explicitly 
created by passing the number of days as the single argument to the 
constructor. To create a duration that involves weeks, months or years, 
boost::gregorian::weeks, boost::gregorian::months and boost::gregorian::years
can be used accordingly.
*/

//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::gregorian::date_duration dd(4); 
//  std::cout << dd.days() << std::endl; 
//  boost::gregorian::weeks ws(4); 
//  std::cout << ws.days() << std::endl; 
//  boost::gregorian::months ms(4); 
//  std::cout << ms.number_of_months() << std::endl; 
//  boost::gregorian::years ys(4); 
//  std::cout << ys.number_of_years() << std::endl; 
//}

/*Download source code
Neither boost::gregorian::months nor boost::gregorian::years allow to 
determine the number of days since months and years vary in length. 
Nonetheless, the usage of these classes can still make sense as shown in 
the following example.
*/

//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::gregorian::date d(2009, 1, 31); 
//  boost::gregorian::months ms(1); 
//  boost::gregorian::date d2 = d + ms; 
//  std::cout << d2 << std::endl; 
//  boost::gregorian::date d3 = d2 - ms; 
//  std::cout << d3 << std::endl; 
//}

/*
The application adds one month to the given date of January 31, 2009 which 
results in d2 being February 28, 2009. In the next step, one month is 
subtracted and d3 becomes January 31, 2009 again. As shown, point in times 
as well as durations can be used in calculations. However, the specifics 
need to be taken into account in these scenarios. For example, starting at 
the last day of a month, boost::gregorian::months always arrives at the 
last day of a different month if jumped forwards or backwards which can 
lead to surprises.
*/

//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::gregorian::date d(2009, 1, 30); 
//  boost::gregorian::months ms(1); 
//  boost::gregorian::date d2 = d + ms; 
//  std::cout << d2 << std::endl; 
//  boost::gregorian::date d3 = d2 - ms; 
//  std::cout << d3 << std::endl; 
//}

/*
This example is identical to the previous one with the exception of d 
being initialized with January 30, 2009. Even though this is not the last
day in January, jumping forward by one month results in d2 becoming 
February 28, 2009 since there is no February 30. However, when jumping 
backwards by one month again, d3 this time actually becomes January 31, 
2009! Since February 28, 2009 is the last day in the month, jumping 
backwards actually returns to the last day in January.
/*
/*
If that behavior is too confusing, it can be modified by revoking the 
definition of the BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES macro. After 
that, the boost::gregorian::weeks, boost::gregorian::months and 
boost::gregorian::years classes are no longer available. The only class 
left is boost::gregorian::date_duration which simply jumps forward and 
backwards by a specified number of days so that unexpected results are no 
longer possible.
/*

/*
While boost::gregorian::date_duration works with durations, boost::gregorian::date_period
offers support for ranges between two dates.
*/

//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::gregorian::date d1(2009, 1, 30); 
//  boost::gregorian::date d2(2009, 10, 31); 
//  boost::gregorian::date_period dp(d1, d2); 
//  boost::gregorian::date_duration dd = dp.length(); 
//  std::cout << dd.days() << std::endl; 
//  std::cout << d2 - d1 << std::endl;
//}

/*
Two arguments of type boost::gregorian::date specifying the beginning and 
end dates can be passed to the constructor of boost::gregorian::date_period.
Alternatively, the beginning date and a duration of type boost::gregorian::date_duration
can be specified. Please note that the day before the end date is actually
the last day of the period which is important in order to understand the
output of the following example.
*/

//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::gregorian::date d1(2009, 1, 30); 
//  boost::gregorian::date d2(2009, 10, 31); 
//  boost::gregorian::date_period dp(d1, d2); 
//  std::cout << dp.contains(d1) << std::endl; 
//  std::cout << dp.contains(d2) << std::endl; 
//}

/*
The application checks for a specific date within the period using the 
contains() method. Even though both d1 and d2 were passed to the constructor
of boost::gregorian::date_period, contains() returns true only the first
time. Since the end date is not part of the period, contains() returns false 
if called with d2.
*/

/*
boost::gregorian::date_period offers additional methods to e.g. move a 
period or to calculate the intersection of two overlapping periods.

Besides classes for date, durations and periods, Boost.DateTime provides 
iterators as well as different useful free-standing functions as shown in 
the following example.
*/

#include <boost/date_time/gregorian/gregorian.hpp> 
#include <iostream> 

int main() 
{ 
  boost::gregorian::date d(2009, 1, 5); 
  boost::gregorian::day_iterator it(d); 
  std::cout << *++it << std::endl; 
  std::cout << boost::date_time::next_weekday(*it, boost::gregorian::greg_weekday(boost::date_time::Friday)) << std::endl; 
}

/*
In order to jump forward or backward by a day from a specific date, the 
iterator boost::gregorian::day_iterator can be used. With boost::gregorian::week_iterator,
boost::gregorian::month_iterator and boost::gregorian::year_iterator, 
additional iterators are provided to jump by weeks, months or years.

The example also uses the boost::date_time::next_weekday() which returns 
the date of the next weekday based on a given date. The above application 
displays 2009-Jan-09 since this is the first Friday following January 6, 
2009.
*/