/*
The most important class in this library is boost::thread, defined in 
boost/thread.hpp, which is used to create a new thread. The following 
example shows how to apply it.
*/

//#include <boost/thread.hpp> 
//#include <iostream> 
//
//void wait(int seconds) 
//{ 
//  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
//} 
//
//void thread() 
//{ 
//  for (int i = 0; i < 5; ++i) 
//  { 
//    wait(1); 
//    std::cout << i << std::endl; 
//  } 
//} 
//
//int main() 
//{ 
//  boost::thread t(thread); 
//  t.join(); 
//}

/*
The name of the function that should execute within the thread is passed to 
the constructor of boost::thread. Once the variable t in the above example 
is created, the thread() function starts executing in its own 
thread immediately. At this point, thread() executes concurrently with the 
main() function.

To keep the application from terminating, the join() method is called on 
the newly created thread. join() is a blocking call: It blocks the current
thread until the thread, for which join() was called, has terminated. This 
causes main() to wait until thread() has terminated.

As seen in the above example, a particular thread can be accessed via a 
variable such as t in order to e.g. wait for its termination using the 
join() method. However, the thread will continue to execute even if t 
loses its scope and is destroyed. A thread always binds to a variable of 
type boost::thread in the beginning, but once created, depends no longer on 
it. There even exists a method called detach() that allows to decouple a 
variable of type boost::thread from its corresponding thread. Certainly, 
methods such as join() cannot be called afterwards since the variable does 
not represent a valid thread any longer.

Anything that can be done inside a function can also be done inside a 
thread. Ultimately, a thread is no different than a function - except that 
it is executed concurrently. In the example above, five numbers are written 
to the standard output stream using a loop. To slow down the output, every 
iteration of the loop calls the wait() function to stall execution for one 
second. wait() employs a function named sleep() that also originates from 
Boost.Thread and resides in the boost::this_thread namespace.

sleep() either expects a period of time or a specific point in time 
indicating how long or until when the current thread should be stalled. 
By passing an object of type boost::posix_time::seconds, a period of time
is specified in this example. boost::posix_time::seconds comes from the 
Boost.DateTime library that is used by Boost.Thread to manage and process 
time data.
*/

/*
While the previous example shows how to wait for a different thread, the 
following example rather shows how a thread can be interrupted by the 
means of so-called interruption points.
*/

#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

void thread() 
{ 
  std::cout << "Working Thread: "<< boost::this_thread::get_id() << std::endl; 
  try 
  { 
    for (int i = 0; i < 5; ++i) 
    { 
      wait(1); 
      std::cout << i << std::endl; 
    } 
  } 
  catch (boost::thread_interrupted&) 
  { 
  } 
} 

int main() 
{ 
  std::cout << "Main Thread: " << boost::this_thread::get_id() << std::endl; 
  std::cout << boost::thread::hardware_concurrency() << std::endl; 

  boost::thread t(thread); 
  wait(3); 
  t.interrupt(); 
  t.join(); 
}

/*
Calling interrupt() on a thread object interrupts the corresponding thread. 
In this context, interrupted means that an exception of type 
boost::thread_interrupted is thrown inside the thread. However, this only 
happens once the thread reaches an interruption point.

Simply calling interrupt() does not cause anything if the given thread does 
not contain any interruption points. Whenever a thread reaches an 
interruption point it will check whether the interrupt() method has been 
called. Only if it has, a boost::thread_interrupted exception is thrown 
accordingly.
/*

/*
Boost.Thread defines a series of interruption points such as the sleep() 
function. Since sleep() is called five times in the example, the thread 
checks five times whether or not it was interrupted. Between the calls to 
sleep(), the thread can not be interrupted though.

Once the program is executed, it will only print three numbers to the 
standard output stream. This is caused by calling the interrupt() method 
after three seconds inside main(). Thus, the corresponding thread is 
interrupted and throws a boost::thread_interrupted exception accordingly. 
While the exception is correctly caught inside the thread, the catch handler
is empty though. Since the thread() function returns after the handler, the 
thread is terminated as well. This in turn will also terminate the entire 
application since main() simply waited for the thread to terminate using 
the join() method.
*/

/*
Boost.Thread defines about ten interruption points including the mentioned 
sleep() function. Thanks to these interruption points, threads can easily 
be interrupted in a timely manner. However, they may not always be the best 
choice since an interruption point must be reached first in order to check 
for the boost::thread_interrupted exception.

To provide a rough overview over the different functions provided by 
Boost.Thread, the following example introduces two more.
*/

//#include <boost/thread.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  std::cout << boost::this_thread::get_id() << std::endl; 
//  std::cout << boost::thread::hardware_concurrency() << std::endl; 
//}

/*
Using the namespace boost::this_thread, independent functions are provided 
that apply to the current thread such as the sleep() function shown before. 
Another one is get_id(): It will return a number identifying the current 
thread. It is also provided as a method for boost::thread.

The static hardware_concurrency() method, provided by the boost::thread 
class, returns the number of threads that could physically be executed at 
the same time based on the underlying number of CPUs or CPU cores. Calling 
this function on a commonly used dual-core machine, a value of 2 is returned.
This allows for a simple method to identify the theoretical maximum number 
of threads that should be used simultaneously by a given multithreaded 
application.
*/