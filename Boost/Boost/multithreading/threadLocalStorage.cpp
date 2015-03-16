/*
Thread Local Storage (TLS) is a dedicated storage area that can only be 
accessed by one thread. TLS variables can be seen as global variables only 
visible to a particular thread instead of the whole program. The following 
example shows the benefits of these variables.
*/

//#include <boost/thread.hpp> 
//#include <iostream> 
//#include <cstdlib> 
//#include <ctime> 
//
//void init_number_generator() 
//{ 
//  static bool done = false; 
//  if (!done) 
//  { 
//    done = true; 
//    std::srand(static_cast<unsigned int>(std::time(0))); 
//  } 
//} 
//
//boost::mutex mutex; 
//
//void random_number_generator() 
//{ 
//  init_number_generator(); 
//  int i = std::rand(); 
//  boost::lock_guard<boost::mutex> lock(mutex); 
//  std::cout << i << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::thread t[3]; 
//
//  for (int i = 0; i < 3; ++i) 
//    t[i] = boost::thread(random_number_generator); 
//
//  for (int i = 0; i < 3; ++i) 
//    t[i].join(); 
//} 

/*
The example creates three threads, each writing a random number to the 
standard output stream. The random_number_generator() function utilizes the 
std::rand() function, defined in the C++ standard, to create the random 
numbers. However, the generator used for std::rand() must be properly 
initialized with the std::srand() function. If not, the program will always 
print the same random number.

Initializing the random number generator takes place inside the 
init_number_generator() function with the aid of the std::time() function 
returning the current time. Since this value differs every time the 
application is executed, it is guaranteed that the generator is always 
initialized with a different value and thus provides new random numbers. 
Since the generator only needs to be initialized once, 
init_number_generator() uses a static variable named done as the condition.

If the program is executed a couple of times, it becomes apparent that two 
of the three random numbers written are always the same. The program 
actually has a defect: The generator on which std::rand() is based must be 
initialized for every thread using the function. Therefore, the 
implementation of init_number_generator() is actually incorrect since it 
only calls std::srand() once. Using TLS, this defect can be rectified.
*/

#include <boost/thread.hpp> 
#include <iostream> 
#include <cstdlib> 
#include <ctime> 

void init_number_generator() 
{ 
  static boost::thread_specific_ptr<bool> tls; 
  if (!tls.get()) 
    tls.reset(new bool(false)); 

  if (!*tls) 
  { 
    *tls = true; 
    std::srand(static_cast<unsigned int>(std::time(0))); 
  } 
} 

boost::mutex mutex; 

void random_number_generator() 
{ 
  init_number_generator(); 
  int i = std::rand(); 
  boost::lock_guard<boost::mutex> lock(mutex); 
  std::cout << i << std::endl; 
} 

int main() 
{ 
  boost::thread t[3]; 

  for (int i = 0; i < 3; ++i) 
    t[i] = boost::thread(random_number_generator); 

  for (int i = 0; i < 3; ++i) 
    t[i].join(); 
}

/*
The static variable done has been replaced with a TLS variable tls which is 
based on the template class boost::thread_specific_ptr - instantiated with 
the data type bool. In principle, tls works just like done: It acts as a 
condition indicating whether or not the random number generator has already 
been initialized. The crucial difference, however, is that the value stored 
by tls is only visible and available to the corresponding thread.

Once a variable of type boost::thread_specific_ptr is created, it can be set 
accordingly. However, it now expects the address of a variable of type bool 
instead of the variable itself. Using the reset() method, the corresponding 
address can be stored in tls. In the given example, a variable of type bool 
is dynamically allocated and its address, returned by new, is stored in tls.
To avoid setting tls every time the init_number_generator() function is 
called, it first checks whether an address is already stored via the get() 
method.

Since boost::thread_specific_ptr stores an address, it behaves like a 
regular pointer. Consequently, both the operator*() and operator->() 
operators are overloaded to simplify the usage. The example uses *tls to 
check whether the condition is currently true or false. Depending on the 
current condition, the random number generator is either initialized or not.

As seen, boost::thread_specific_ptr allows storing the address of an object 
for the current thread and only allows the current thread to retrieve the 
same address later on. While one thread already stored the address 
successfully, a different thread may have not.

If the program is now executed, it may come as a surprise that despite the 
TLS variable, the random numbers generated are still equal. This is due to 
the fact that all three threads are created at the same time and thus, the 
random number generators are initialized with the same time as well. If the 
program is executed a couple of times however, the random numbers will 
change indicating that the generators itself are initialized correctly.
*/