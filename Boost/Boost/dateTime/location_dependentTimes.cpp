/*
Unlike the location-independent times introduced in the previous section, 
location-dependent times actually account for time zones. For this purpose,
Boost.DateTime offers the boost::local_time::local_date_time class, defined 
in boost/date_time/local_time/local_time.hpp, which uses 
boost::local_time::posix_time_zone to store time zone information.
*/

//#include <boost/date_time/local_time/local_time.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::local_time::time_zone_ptr tz(new boost::local_time::posix_time_zone("CET+1")); 
//  boost::posix_time::ptime pt(boost::gregorian::date(2009, 1, 5), boost::posix_time::time_duration(12, 0, 0)); 
//  boost::local_time::local_date_time dt(pt, tz); 
//  std::cout << dt.utc_time() << std::endl; 
//  std::cout << dt << std::endl; 
//  std::cout << dt.local_time() << std::endl; 
//  std::cout << dt.zone_name() << std::endl; 
//}

/*
The constructor of boost::local_time::local_date_time expects an object of 
type boost::posix_time::ptime as its first argument as well as an object of 
type boost::local_time::time_zone_ptr as its second. This is merely a type
definition for boost::shared_ptr<boost::local_time::posix_time_zone>. In 
other words, no object of type boost::local_time::posix_time_zone is passed
but rather a smart pointer pointing to one. This allows multiple objects of 
type boost::local_time::local_date_time to share time zone information. 
Only if the last object is destroyed, the corresponding object representing
the time zone is automatically released.
*/

/*
To create an object of type boost::local_time::posix_time_zone, a string 
describing the time zone is passed to the constructor as the single argument.
The above example specifies Central Europe as the time zone: CET is the 
abbreviation for Central European Time. Since CET is one hour ahead of UTC, 
the deviation is denoted as +1 accordingly. Boost.DateTime is not able to 
interpret abbreviations for time zones and thus does not know the meaning 
of CET. Therefore, the deviation must always be provided in hours; 
passing +0 means no deviation.
/*

/*
When executed, the application will write 2009-Jan-05 12:00:00, 
2009-Jan-05 13:00:00 CET, 2009-Jan-05 13:00:00 and CET to the standard 
output stream. Values used to initialize objects of type 
boost::posix_time::ptime and boost::local_time::local_date_time always 
relate to the UTC time zone by default. Only if an object of type 
boost::local_time::local_date_time is written to the standard output stream 
or a call to the local_time() method is made, the deviation in hours is 
used for calculating the local time.
*/

#include <boost/date_time/local_time/local_time.hpp> 
#include <iostream> 

int main() 
{ 
  boost::local_time::time_zone_ptr tz(new boost::local_time::posix_time_zone("CET+1")); 
  boost::posix_time::ptime pt(boost::gregorian::date(2009, 1, 5), boost::posix_time::time_duration(12, 0, 0)); 
  boost::local_time::local_date_time dt(pt, tz); 
  std::cout << dt.local_time() << std::endl; 
  boost::local_time::time_zone_ptr tz2(new boost::local_time::posix_time_zone("EET+2")); 
  std::cout << dt.local_time_in(tz2).local_time() << std::endl; 
}

/*
By using the local_time() method, the deviation for the time zone is 
actually respected. In order to calculate the CET time, one hour needs to 
be added to the UTC time of 12 PM stored in dt since CET is one hour ahead 
of UTC. local_time() writes 2009-Jan-05 13:00:00 to the standard output 
stream accordingly.

In contrast, the local_time_in() method interprets the time stored in dt as
being in the time zone passed as the argument. This means that 12 PM UTC 
equals 2 PM EET which stands for Eastern European Time and is two hours 
ahead of UTC.

Finally, location-dependent periods are offered by Boost.DateTime via the 
boost::local_time::local_time_period class.
*/

//#include <boost/date_time/local_time/local_time.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::local_time::time_zone_ptr tz(new boost::local_time::posix_time_zone("CET+0")); 
//  boost::posix_time::ptime pt1(boost::gregorian::date(2009, 1, 5), boost::posix_time::time_duration(12, 0, 0)); 
//  boost::local_time::local_date_time dt1(pt1, tz); 
//  boost::posix_time::ptime pt2(boost::gregorian::date(2009, 1, 5), boost::posix_time::time_duration(18, 0, 0)); 
//  boost::local_time::local_date_time dt2(pt2, tz); 
//  boost::local_time::local_time_period tp(dt1, dt2); 
//  std::cout << tp.contains(dt1) << std::endl; 
//  std::cout << tp.contains(dt2) << std::endl; 
//}

/*
The constructor of boost::local_time::local_time_period expects two 
arguments of type boost::local_time::local_date_time. As with the other 
data types provided for periods, the second argument, representing the end 
time, is not part of the actual period. With the help of methods such as 
contains(), intersection(), merge() and others, periods can be processed 
with boost::local_time::local_time_period accordingly.
*/