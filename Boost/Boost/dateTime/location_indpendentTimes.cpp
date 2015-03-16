/*
While boost::gregorian::date creates a date, boost::posix_time::ptime is u
sed to define a location-independent time. boost::posix_time::ptime 
accesses boost::gregorian::date but stores a time in addition.

In order to use boost::posix_time::ptime the header boost/date_time/posix_time/posix_time.hpp needs to be included.
*/

//#include <boost/date_time/posix_time/posix_time.hpp> 
//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::posix_time::ptime pt(boost::gregorian::date(2009, 1, 5), boost::posix_time::time_duration(12, 0, 0)); 
//  boost::gregorian::date d = pt.date(); 
//  std::cout << d << std::endl; 
//  boost::posix_time::time_duration td = pt.time_of_day(); 
//  std::cout << td << std::endl; 
//}

/*
To initialize an object of type boost::posix_time::ptime, a date of type 
boost::gregorian::date and a duration of type boost::posix_time::time_duration 
is passed as the first and second argument to the constructor. The three 
arguments passed to the constructor of boost::posix_time::time_duration 
determine the time. The above application specifies 12 PM on January 5, 
2009 as the point in time.

In order to query date and time, the date() and time_of_day() methods can 
be used.
*/

/*
Just like the default constructor of boost::gregorian::date creates an 
invalid date, a time of type boost::posix_time::ptime is also invalid if 
the default constructor is used. An invalid time can also be created 
explicitly by passing boost::date_time::not_a_date_time to the constructor.

Similar to creating calendar dates of type boost::gregorian::date via the 
use of free-standing functions or methods of different objects, 
Boost.DateTime offers corresponding free-standing functions and objects to 
create times.
*/

//#include <boost/date_time/posix_time/posix_time.hpp> 
//#include <boost/date_time/gregorian/gregorian.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::posix_time::ptime pt = boost::posix_time::second_clock::universal_time(); 
//  std::cout << pt.date() << std::endl; 
//  std::cout << pt.time_of_day() << std::endl; 
//
//  pt = boost::posix_time::from_iso_string("20090105T120000"); 
//  std::cout << pt.date() << std::endl; 
//  std::cout << pt.time_of_day() << std::endl; 
//}

/*
The boost::posix_time::second_clock class represents a clock returning the 
current time. The universal_time() method returns the UTC time as shown in 
the above example. If local time is preferred, local_time() must be used.
*/

/*
Boost.DateTime offers an additional class named boost::posix_time::microsec_clock
that returns the current time including microseconds in case a higher 
resolution is required.

To convert a point in time stored in a string to an object of type 
boost::posix_time::ptime, free-standing functions such as boost::posix_time::from_iso_string() 
are provided which expects the point in time to be stored in the ISO 8601 
format.

In addition to boost::posix_time::ptime, Boost.DateTime also offers the 
boost::posix_time::time_duration class that specifies a duration. This 
class has been mentioned before since the constructor of boost::posix_time::ptime 
actually expects an object of type boost::posix_time::time_duration as its 
second argument. Nonetheless, boost::posix_time::time_duration can certainly
be used independently as well.
*/

//#include <boost/date_time/posix_time/posix_time.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::posix_time::time_duration td(16, 30, 0); 
//  std::cout << td.hours() << std::endl; 
//  std::cout << td.minutes() << std::endl; 
//  std::cout << td.seconds() << std::endl; 
//  std::cout << td.total_seconds() << std::endl; 
//}

/*
hours(), minutes() and seconds() all return values that are passed to the 
constructor while methods such as total_seconds(), returning the total 
number of seconds, provide one with additional information in a simple way.

/*
Random values can be legally passed to boost::posix_time::time_duration 
since no upper limit such as 24 hours exists.

As with calendar dates, calculations can also be performed with points in 
time and durations.
*/

//#include <boost/date_time/posix_time/posix_time.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::posix_time::ptime pt1(boost::gregorian::date(2009, 1, 05), boost::posix_time::time_duration(12, 0, 12)); 
//  boost::posix_time::ptime pt2(boost::gregorian::date(2009, 1, 05), boost::posix_time::time_duration(18, 30, 0)); 
//  boost::posix_time::time_duration td = pt2 - pt1; 
//  std::cout << td.hours() << std::endl; 
//  std::cout << td.minutes() << std::endl; 
//  std::cout << td.seconds() << std::endl; 
//}

/*
If two times of type boost::posix_time::ptime are subtracted from each 
other, the result is an object of type boost::posix_time::time_duration 
specifying the duration between the two points.
*/

//#include <boost/date_time/posix_time/posix_time.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::posix_time::ptime pt1(boost::gregorian::date(2009, 1, 05), boost::posix_time::time_duration(12, 0, 0)); 
//  boost::posix_time::time_duration td(6, 30, 0); 
//  boost::posix_time::ptime pt2 = pt1 + td; 
//  std::cout << pt2.time_of_day() << std::endl; 
//}

/*
As shown in the example, a duration can be added to a specific point in 
time resulting in a new point in time. The above application writes 
18:30:00 to the standard output stream.
*/

/*
As one may have been noticed, Boost.DateTime uses the same concepts for 
both calendar dates and times. Just like there are classes for times and 
durations, there is also one for periods. For calendar dates, this class is
boost::gregorian::date_period; for times it is boost::posix_time::time_period.
Both classes expect two arguments being passed to the constructor: 
boost::gregorian::date_period expects two calendar dates while boost::posix_time::time_period
expects two times.
*/

//#include <boost/date_time/posix_time/posix_time.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::posix_time::ptime pt1(boost::gregorian::date(2009, 1, 05), boost::posix_time::time_duration(12, 0, 0)); 
//  boost::posix_time::ptime pt2(boost::gregorian::date(2009, 1, 05), boost::posix_time::time_duration(18, 30, 0)); 
//  boost::posix_time::time_period tp(pt1, pt2); 
//  std::cout << tp.contains(pt1) << std::endl; 
//  std::cout << tp.contains(pt2) << std::endl; 
//}

/*
In general boost::posix_time::time_period works exactly like 
boost::gregorian::date_period. It provides a method named contains() which
returns true for every point in time within the period. Since the end time,
passed to the constructor of boost::posix_time::time_period, is not part of
the period, above example returns false for the second call of contains().
*/

/*
boost::posix_time::time_period also offers additional methods such as 
intersection() and merge() to calculate the intersection of two overlapping
periods or to merge two intersecting periods, respectively.

Finally, the iterator boost::posix_time::time_iterator is introduced to i
terate over points in time.
*/

#include <boost/date_time/local_time/local_time.hpp> 
#include <iostream> 

int main() 
{ 
  boost::posix_time::ptime pt(boost::gregorian::date(2009, 1, 05), boost::posix_time::time_duration(12, 0, 0)); 
  boost::posix_time::time_iterator it(pt, boost::posix_time::time_duration(6, 30, 0)); 
  std::cout << *++it << std::endl; 
  std::cout << *++it << std::endl; 
}

/*
The application uses the iterator it to jump forward 6.5 hours starting at
time pt. Since the iterator is incremented twice, the corresponding output
is 2009-Jan-05 18:30:00 and 2009-Jan-06 01:00:00.
*/