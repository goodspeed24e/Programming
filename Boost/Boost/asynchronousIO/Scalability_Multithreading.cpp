/*
Developing an application using a library such as Boost.Asio differs from 
the usual C++ style. Functions that may take longer to return are no longer 
called in a sequential manner. Instead of calling blocking functions, 
Boost.Asio starts asynchronous operations instead. Functions that are 
required to be called once the operation has finished are implemented 
within the corresponding handler. The drawback of this approach is the 
physical separation of the sequentially executed functions which certainly 
makes the corresponding code more difficult to understand.

A library such as Boost.Asio is typically used to achieve a higher 
efficiency of the application. Without the need to wait for a particular 
function to finish, an application can perform other tasks in between, e.g. 
starting another operation that may take a while to complete.

Scalability describes the property of an application to effectively benefit 
from additional resources. Using Boost.Asio is already recommended if 
long-lasting operations should not block other operations. Since today's 
PCs are typically equipped with multi-core processors, the usage of threads 
can increase the scalability of an application based on Boost.Asio even 
further.

If the run() method is called on an object of type boost::asio::io_service, 
the associated handlers are invoked within the same thread. By using 
multiple threads, an application can call multiple run() methods 
simultaneously. Once an asynchronous operation has finished, the 
corresponding I/O service will then execute the handler within one of the 
threads. If a second operation has finished shortly after the first, the 
I/O service can execute the handler within a different thread without 
needing to wait for the first handler to terminate.
*/

//#include <boost/asio.hpp> 
//#include <boost/thread.hpp> 
//#include <iostream> 
//
//void handler1(const boost::system::error_code &ec) 
//{ 
//  std::cout << "5 s." << std::endl; 
//} 
//
//void handler2(const boost::system::error_code &ec) 
//{ 
//  std::cout << "5 s." << std::endl; 
//} 
//
//boost::asio::io_service io_service; 
//
//void run() 
//{ 
//  io_service.run(); 
//} 
//
//int main() 
//{ 
//  boost::asio::deadline_timer timer1(io_service, boost::posix_time::seconds(5)); 
//  timer1.async_wait(handler1); 
//  boost::asio::deadline_timer timer2(io_service, boost::posix_time::seconds(5)); 
//  timer2.async_wait(handler2); 
//
//	// check thread number
//  boost::thread thread1(run); 
//  boost::thread thread2(run); 
//  thread1.join(); 
//  thread2.join(); 
//}

/*
Both threads are calling the run() method for the single I/O service. This 
allows the I/O service to utilize both threads for executing handler 
functions once individual asynchronous operations have completed.

Both timers in the example application are set to elapse after five seconds.
Since two threads are available, both handler1() and handler2() can be 
executed simultaneously. If the second timer elapses while the handler of 
the first one is still executed, the second handler is executed within the 
second thread. If the handler of the first timer has already terminated, the
I/O service is free to choose either thread.
*/

/*
Threads can increase the performance of an application. Since threads are 
executed on processor cores, there is no sense in creating more threads 
than there are cores. This ensures that each thread is executed on its own 
core without battling with other threads for the corresponding core.
*/

/*
Please note that the usage of threads does not always make sense. Running 
the above example can result in a mixed output of the individual messages 
on the standard output stream since the two handlers, which may run in 
parallel, access a single shared resource: The standard output stream 
std::cout. The access needs to be synchronized in order to guarantee that 
each message is written completely before a different thread can write 
another message to the standard output stream. The usage of threads in this 
scenario does not provide much benefit as long as the individual handlers 
cannot be independently executed in parallel.

Calling the run() method of a single I/O service multiple times is the 
recommended way of adding scalability to any application based on 
Boost.Asio. Alternatively, there is a different method: Instead of 
binding multiple threads to a single I/O service, multiple I/O services can 
be created instead. Each of the I/O services then utilizes one thread. If 
the number of I/O services matches the number of processor cores on the 
system, asynchronous operations can be executed on their own core.
*/

#include <boost/asio.hpp> 
#include <boost/thread.hpp> 
#include <iostream> 

void handler1(const boost::system::error_code &ec) 
{ 
  std::cout << "5 s." << std::endl; 
} 

void handler2(const boost::system::error_code &ec) 
{ 
  std::cout << "5 s." << std::endl; 
} 

boost::asio::io_service io_service1; 
boost::asio::io_service io_service2; 

void run1() 
{ 
  io_service1.run(); 
} 

void run2() 
{ 
  io_service2.run(); 
} 

int main() 
{ 
  boost::asio::deadline_timer timer1(io_service1, boost::posix_time::seconds(5)); 
  timer1.async_wait(handler1); 
  boost::asio::deadline_timer timer2(io_service2, boost::posix_time::seconds(5)); 
  timer2.async_wait(handler2); 

  // check thread number
  boost::thread thread1(run1); 
  boost::thread thread2(run2); 
  thread1.join(); 
  thread2.join(); 
}

/*
The already known example application using two timers has now been 
rewritten to utilize two I/O services. The application is still based on 
two threads; however, each thread is now bound to an individual I/O service.
Additionally, the two I/O objects timer1 and timer2 are now also bound to 
the different I/O services.

The functionality of the application is the same as before. It can be
beneficial under certain conditions to have multiple I/O services, each 
with its own thread and ideally running on its own processor core, since 
asynchronous operations including their handlers then can execute locally. 
If no distant data or function needs to be accessed, each I/O service acts 
as a small autonomous application. Local and distant in this case refers to 
resources such as cache and memory pages. Since specific knowledge about 
the underlying hardware, operation system, compiler as well as potential 
bottlenecks is required before optimization strategies can be developed, 
multiple I/O services should only be used in scenarios that clearly benefit 
from them.
*/