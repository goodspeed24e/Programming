/*
Applications utilizing Boost.Asio for asynchronous data processing are 
based on so-called I/O services and I/O objects. While I/O services 
abstract operating system interfaces that allow asynchronous data 
processing in the first place, I/O objects are used to initiate certain 
operations. Whereas Boost.Asio only provides one class named 
boost::asio::io_service for the I/O service, implemented as an optimized 
class for each operating system supported, it contains several classes for 
the individual I/O objects. Among these, the class boost::asio::ip::tcp::socket 
is used to send and receive data over a network while the class 
boost::asio::deadline_timer offers a timer that either elapses at a fixed 
point in time or after a certain period. The timer is used in the following 
first example since it does not require any knowledge about network 
programming compared to many of the remaining I/O objects provided by Asio.
*/

//#include <boost/asio.hpp> 
//#include <iostream> 
//
//void handler(const boost::system::error_code &ec) 
//{ 
//  std::cout << "5 s." << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::asio::io_service io_service; 
//  boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(5)); 
//  timer.async_wait(handler); 
//  io_service.run(); 
//}

/*
The function main() first defines an I/O service io_service that is used to 
initialize the I/O object timer. Just like boost::asio::deadline_timer, all 
I/O objects typically expect an I/O service as their first argument to the 
constructor. Since timer resembles an alarm, the constructor of 
boost::asio::deadline_timer can be passed a second argument indicating 
either a point in time or a period after which the alarm should go off. 
The above example specifies a period of five seconds for the alarm which 
starts counting once timer has been defined.
*/

/*
While it would be possible to call a function that returns after five 
seconds, an asynchronous operation is started with Asio by calling the 
method async_wait() and passing the name of the handler() function as the 
single argument. Please note that only the name of the handler() function 
is passed but the function itself is not called.

The advantage of async_wait() is that the function call returns immediately 
instead of waiting five seconds. Once the alarm goes off, the function 
provided as the argument is called accordingly. The application thus can 
execute other operations after calling async_wait() instead of just blocking.
*/

/*
A method such as async_wait() is described as non-blocking. I/O objects 
typically also provide blocking methods in case the execution flow should 
be blocked until a certain operation has finished. For example, the 
blocking wait() method could have been called for 
boost::asio::deadline_timer instead. Since it is a blocking call, it does 
not require a function name but rather returns at a specific point in time 
or after a certain period.

While looking at the source code of the above example, it can be noticed 
that after the call to async_wait(), a method named run() is called on the 
I/O service. This is mandatory since control needs to be taken over by the 
operating system in order to call the handler() function after five seconds.

While async_wait() starts an asynchronous operation and returns 
immediately, run() actually blocks. Execution therefore stops at the call 
of run(). Ironically, many operating systems support asynchronous 
operations via a blocking function only. The following example shows why 
this limitations is typically not an issue.
*/

#include <boost/asio.hpp> 
#include <iostream> 

void handler1(const boost::system::error_code &ec) 
{ 
  std::cout << "5 s." << std::endl; 
} 

void handler2(const boost::system::error_code &ec) 
{ 
  std::cout << "10 s." << std::endl; 
} 

int main() 
{ 
  boost::asio::io_service io_service; 
  boost::asio::deadline_timer timer1(io_service, boost::posix_time::seconds(5)); 
  timer1.async_wait(handler1); 
  boost::asio::deadline_timer timer2(io_service, boost::posix_time::seconds(10)); 
  timer2.async_wait(handler2); 
  io_service.run(); 
}

/*
The above application now utilizes two I/O objects of type 
boost::asio::deadline_timer. The first I/O object represents an alarm going 
off after five seconds while the second one represents an alarm going off 
after ten seconds. After each period has elapsed, the functions handler1() 
and handler2() are called accordingly.

The run() method is again called on the sole I/O service at the end of 
main(). As previously mentioned, this function actually blocks execution 
passing control to the operating system which takes over the asynchronous 
processing. With the aid of the operating system, the handler1() function 
is called after five seconds while the handler2() function is called after 
10 seconds, respectively.
*/

/*
At first sight, it may come as a surprise that asynchronous processing 
requires calling the blocking run() method. However, since the application 
needs to be prevented from terminating, this does actually not pose any 
issue. If run() would not block, main() would actually finish and thus 
terminate the application. If execution of the application should not be 
blocked, run() should be called within a new thread since it naturally 
blocks the current thread only.

Once all asynchronous operations of the particular I/O service have been 
completed, controls is returned back to the run() method which simply 
returns. Both example applications terminate once all the alarms have 
gone off.
*/