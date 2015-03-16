/*
While the usage of multiple threads can increase the performance of an 
application it usually also increases its complexity. If several functions 
execute at the same time using threads, access to shared resources must be 
synchronized accordingly. This involves quite some work once the application 
reaches a certain size. This paragraph introduces the classes provided by 
Boost.Thread for synchronizing threads.
*/

//#include <boost/thread.hpp> 
//#include <iostream> 
//
//void wait(int seconds) 
//{ 
//  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
//} 
//
//boost::mutex mutex; 
//
//void thread() 
//{ 
//  for (int i = 0; i < 5; ++i) 
//  { 
//    wait(1); 
//    mutex.lock(); 
//    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 
//    mutex.unlock(); 
//  } 
//} 
//
//int main() 
//{ 
//  boost::thread t1(thread); 
//  boost::thread t2(thread); 
//  t1.join(); 
//  t2.join(); 
//}

/*
Multithreaded programs use so-called mutex objects for synchronization. 
Boost.Thread provides different mutex classes, boost::mutex being the most 
simple one. The basic principle of a mutex is to prevent other threads from 
taking ownership while a particular thread owns it. Once released, a 
different thread can take ownership. This causes threads to wait until a 
different thread has finished processing some operations and thus releases 
its ownership of the mutex object accordingly. 
*/

/*
The above example uses a global mutex object of type boost::mutex named 
mutex. The thread() function takes ownership of this object right before 
it writes to the standard output stream inside the for loop using the lock() 
method. Once a message has been written, the ownership is released using 
the unlock() method.

main() creates two threads, both executing the thread() function. Using the 
for loop, every thread counts to five, writing a message to the standard 
output stream with each iteration. Unfortunately, the standard output 
stream is a global object which is shared among all threads. The standard 
does not provide any guarantee that std::cout can be safely accessed from 
multiple threads. Thus, access to the standard output stream must be 
synchronized: At any given time, only one thread is allowed to access 
std::cout.
*/

/*
Since both threads try to acquire the mutex before writing to the standard 
output stream, it is guaranteed that only one thread at a time actually 
accesses std::cout. Disregarding which thread successfully calls the lock() 
method, all other threads need to wait until unlock() has been called.

Acquiring and releasing mutexes is a typical scheme and is supported by 
Boost.Thread through different data types. For example, instead of calling 
lock() and unlock() directly, the boost::lock_guard class can be used.
*/

//#include <boost/thread.hpp> 
//#include <iostream> 
//
//void wait(int seconds) 
//{ 
//  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
//} 
//
//boost::mutex mutex; 
//
//void thread() 
//{ 
//  for (int i = 0; i < 5; ++i) 
//  { 
//    wait(1); 
//    boost::lock_guard<boost::mutex> lock(mutex); 
//    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 
//  } 
//} 
//
//int main() 
//{ 
//  boost::thread t1(thread); 
//  boost::thread t2(thread); 
//  t1.join(); 
//  t2.join(); 
//}

/*
boost::lock_guard automatically calls lock() and unlock() inside its 
constructor and destructor, respectively. Access to the shared resource is 
as synchronized as it was when calling both methods explicitly. 
The boost::lock_guard class is yet another example of the RAII idiom 
presented in Chapter 2, Smart Pointers.
*/

/*
Besides boost::mutex and boost::lock_guard, Boost.Thread provides 
additional classes to support variations of synchronization. One of the 
essential ones is boost::unique_lock which, compared to boost::lock_guard, 
provides a number of helpful methods.
*/

//#include <boost/thread.hpp> 
//#include <iostream> 
//
//void wait(int seconds) 
//{ 
//  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
//} 
//
//boost::timed_mutex mutex; 
//
//void thread() 
//{ 
//  for (int i = 0; i < 5; ++i) 
//  { 
//    wait(1); 
//    boost::unique_lock<boost::timed_mutex> lock(mutex, boost::try_to_lock); 
//    if (!lock.owns_lock()) 
//      lock.timed_lock(boost::get_system_time() + boost::posix_time::seconds(1)); 
//    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 
//    boost::timed_mutex *m = lock.release(); 
//    m->unlock(); 
//  } 
//} 
//
//int main() 
//{ 
//  boost::thread t1(thread); 
//  boost::thread t2(thread); 
//  t1.join(); 
//  t2.join(); 
//}

/*
The above example uses various methods to illustrate some of the features 
provided by boost::unique_lock. Certainly, the usage of these features does 
not necessarily make sense for the given scenario; the usage of 
boost::lock_guard in the previous example was already adequate. This example 
is rather meant to demonstrate the possibilities offered by 
boost::unique_lock.

boost::unique_lock offers different ways of acquiring a mutex by providing 
multiple constructors. The one expecting only a mutex object simply calls 
the lock() method and waits until the mutex has been acquired. It thus acts 
exactly the same as the one of boost::lock_guard.
*/

/*
If a value of type boost::try_to_lock is passed as the second parameter, the 
corresponding constructor calls try_lock() instead. This method returns a 
value of type bool: true if the mutex could be acquired, false if not. 
Opposed to the lock() method, try_lock() returns immediately and does not 
block until the mutex has been acquired.

The above program passes boost::try_to_lock as the second parameter to the 
constructor of boost::unique_lock. Whether or not the mutex has been 
acquired can be checked via the owns_lock() method afterwards. In case it 
has not - owns_lock() returns false - another function provided by 
boost::unique_lock is used: timed_lock() waits for a certain time to 
acquire the mutex. The given program waits for up to one second which 
should be more than enough time to acquire the mutex.
*/

/*
The example actually shows the three fundamental ways of acquiring a 
mutex: lock() waits until the mutex has been acquired. try_lock() does not 
wait but acquires the mutex if it is available at the time of the call and 
returns false otherwise. Finally, timed_lock() tries to acquire the mutex 
within a given period of time. As with try_lock(), success or failure is 
indicated by the return value of type bool.

While both lock() and try_lock() are provided by boost::mutex, timed_lock() 
is only supported by boost::timed_mutex instead which is the reason for its 
usage in the above example program. Without using timed_lock(), the mutex 
can be of type boost::mutex as seen in the previous example.

Just like boost::lock_guard, the destructor of boost::unique_lock releases 
the mutex accordingly. In addition, the mutex can be manually released 
using the unlock() method. It is also possible to remove the association 
between the boost::unique_lock class and the mutex by calling release() as 
done in the above example. In this case however, the mutex must be released 
using the unlock() method explicitly as it is not done automatically by the 
destructor of boost::unique_lock anymore.
*/

/*
boost::unique_lock is a so-called exclusive lock meaning that only one 
thread at a time can acquire the mutex. Other threads are required to wait 
until the mutex has been released again. Besides exclusive locks there are 
also non-exclusive ones. Boost.Thread provides a class named 
boost::shared_lock to support non-exclusive locks accordingly. This class 
must be used together with a mutex of type boost::shared_mutex as shown in 
the following example.
*/

//#include <boost/thread.hpp> 
//#include <iostream> 
//#include <vector> 
//#include <cstdlib> 
//#include <ctime> 
//
//void wait(int seconds) 
//{ 
//  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
//} 
//
//boost::shared_mutex mutex; 
//std::vector<int> random_numbers; 
//
//void fill() 
//{ 
//  std::srand(static_cast<unsigned int>(std::time(0))); 
//  for (int i = 0; i < 3; ++i) 
//  { 
//    boost::unique_lock<boost::shared_mutex> lock(mutex); 
//    random_numbers.push_back(std::rand()); 
//    lock.unlock(); 
//    wait(1); 
//  } 
//} 
//
//void print() 
//{ 
//  for (int i = 0; i < 3; ++i) 
//  { 
//    wait(1); 
//    boost::shared_lock<boost::shared_mutex> lock(mutex); 
//    std::cout << random_numbers.back() << std::endl; 
//  } 
//} 
//
//int sum = 0; 
//
//void count() 
//{ 
//  for (int i = 0; i < 3; ++i) 
//  { 
//    wait(1); 
//    boost::shared_lock<boost::shared_mutex> lock(mutex); 
//    sum += random_numbers.back(); 
//  } 
//} 
//
//int main() 
//{ 
//  boost::thread t1(fill); 
//  boost::thread t2(print); 
//  boost::thread t3(count); 
//  t1.join(); 
//  t2.join(); 
//  t3.join(); 
//  std::cout << "Summe: " << sum << std::endl; 
//}

/*
Non-exclusive locks of type boost::shared_lock can be used if threads only 
need read-only access to a specific resource. A thread modifying the 
resource needs write access and thus requires an exclusive lock. The reason 
for that should be obvious: Threads with read-only access do not recognize 
other threads accessing the same resource at the same time. Non-exclusive 
locks can therefore share a mutex.

In the given example, both print() and count() access random_numbers 
read-only. While the print() function writes the last number of 
random_numbers to the standard output stream, the count() function adds it 
to the variable sum. Since neither function modifies random_numbers, both 
can access it at the same time using a non-exclusive lock of type 
boost::shared_lock.
*/

/*
Inside the fill() function, an exclusive lock of type boost::unique_lock is 
required since it inserts new random numbers into random_numbers. 
The mutex is explicitly released using the unlock() method before fill() 
waits for one second. Opposed to the previous example, wait() is called at 
the end of the for loop to guarantee that at least one random number exists 
in the container before it is accessed by either print() or count(). 
Both of these functions call the wait() function at the beginning of their 
for loop accordingly.

Looking at the individual calls to the wait() function from different 
locations, one potential issue becomes apparent: The order of the function 
calls is directly affected by the order in which the CPU actually executes 
the individual threads. Using so-called condition variables, the individual 
threads can be synchronized so that elements added to random_numbers are 
immediately processed by a different thread accordingly.
*/

#include <boost/thread.hpp> 
#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 

boost::mutex mutex; 
boost::condition_variable_any cond; 
std::vector<int> random_numbers; 

void fill() 
{ 
  std::srand(static_cast<unsigned int>(std::time(0))); 
  for (int i = 0; i < 3; ++i) 
  { 
    boost::unique_lock<boost::mutex> lock(mutex); 
    random_numbers.push_back(std::rand()); 
    cond.notify_all(); 
    cond.wait(mutex); 
  } 
} 

void print() 
{ 
  std::size_t next_size = 1; 
  for (int i = 0; i < 3; ++i) 
  { 
    boost::unique_lock<boost::mutex> lock(mutex); 
    while (random_numbers.size() != next_size) 
      cond.wait(mutex); 
    std::cout << random_numbers.back() << std::endl; 
    ++next_size; 
    cond.notify_all(); 
  } 
} 

int main() 
{ 
  boost::thread t1(fill); 
  boost::thread t2(print); 
  t1.join(); 
  t2.join(); 
}

/*
The program in this example removed the wait() and count() functions. 
Threads do no longer wait for one second with every loop iteration but 
rather execute as fast as possible. Additionally, no total is calculated; 
numbers are solely written to the standard output stream.

To ensure correct processing of the random numbers, the individual threads 
are synchronized by a conditional variable that allows to check for certain 
conditions between multiple threads.

As before, the fill() function generates a random number with each iteration
and places it in the random_numbers container. To block other threads from 
accessing the container at the same time, an exclusive lock is taken 
accordingly. Instead of waiting for one second, this example actually uses 
a conditional variable instead. Calling the notify_all() method will wake up
every thread that has been waiting for this notification by calling the 
wait() method, respectively.

By looking at the for loop of the print() function, one can see that for the 
same conditional variable a method named wait() is called. If the thread is 
woken up by a call to notify_all(), it tries to acquire the mutex which 
will only succeed after it has been successfully released in the fill() 
function.

The trick here is that calling wait() also releases the corresponding mutex 
passed as parameter. After calling notify_all(), the fill() function 
releases the mutex by calling wait() accordingly. It then blocks and waits 
for some other thread to call notify_all() which happens in the print() 
function once the random number has been written to the standard output 
stream.

Notice that the call to the wait() method inside the print() function 
actually happens within a separate while loop. This is done to handle the 
scenario where a random number has already been placed in the container 
before the wait() method is called for the first time in print(). By 
comparing the number of stored elements in random_numbers with the 
expected number of elements, this scenario is successfully handled and the 
random number is written to the standard output stream.
*/
