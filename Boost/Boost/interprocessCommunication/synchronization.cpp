/*
Boost.Interprocess allows multiple applications to use a shared memory 
concurrently. Since shared memory is by definition "shared" between these 
applications, Boost.Interprocess needs to support some form of 
synchronization.
*/

/*
While thinking about synchronization, the library Boost.Thread certainly 
comes to mind. As can be seen in Chapter 6, Multithreading, Boost.Thread 
indeed provides different concepts such as mutex objects and conditional 
variables to synchronize threads. Unfortunately, these classes can only be 
used to synchronize threads within the same application; they do not 
support the synchronization of different applications. Since the challenge 
in both cases is the same, the concepts are no different.

While synchronization objects such as mutex objects and conditional 
variables reside within the same address space in multithreaded applications 
and therefore are available to all threads, the challenge with shared 
memory is that independent applications need to share these objects 
appropriately. For example, if one application creates a mutex object, it 
needs to be accessible from a different application somehow.
*/

/*
Boost.Interprocess offers two kinds of synchronization objects: Anonymous 
objects are directly stored in the shared memory which makes them 
automatically available to all applications. Named objects are managed by 
the operating system and thus are not stored in the shared memory. They can 
be referenced by applications via their name.

The following example creates and uses a named mutex object by using the 
boost::interprocess::named_mutex class defined in boost/interprocess/sync/named_mutex.hpp.
*/

//#include <boost/interprocess/managed_shared_memory.hpp> 
//#include <boost/interprocess/sync/named_mutex.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024); 
//  int *i = managed_shm.find_or_construct<int>("Integer")(); 
//  std::cout << *i << std::endl; 
//  boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx"); 
//  named_mtx.lock(); 
//  ++(*i); 
//  std::cout << *i << std::endl; 
//  named_mtx.unlock(); 
//}

/*
Besides a parameter specifying whether the mutex object should be created or 
opened, the constructor of boost::interprocess::named_mutex expects a name 
for it. Every application that knows that name is able to open the same 
mutex object. In order to get access to the data in the shared memory, the 
application needs to take ownership of the mutex object by calling the 
lock() method. Since mutex objects can only be owned by one application at 
any time, another application may need to wait until the mutex object has 
been released using the unlock() method by the first application. Once an 
application obtained ownership of a mutex object, it has exclusive access 
to the resource it guards. In the above example the resource is a variable 
of type int that is incremented and written to the standard output stream.
*/
/*
If the application is started multiple times, every instance will print a value incremented by 1 compared to the previous value. Thanks to the mutex object, the access to the shared memory and the variable itself is synchronized between the different applications.

The following application uses an anonymous mutex object of type boost::interprocess::interprocess_mutex defined in boost/interprocess/sync/interprocess_mutex.hpp. In order to be accessible for all applications, it is stored in the shared memory.
*/

//#include <boost/interprocess/managed_shared_memory.hpp> 
//#include <boost/interprocess/sync/interprocess_mutex.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024); 
//  int *i = managed_shm.find_or_construct<int>("Integer")(); 
//  boost::interprocess::interprocess_mutex *mtx = managed_shm.find_or_construct<boost::interprocess::interprocess_mutex>("mtx")(); 
//  mtx->lock(); 
//  ++(*i); 
//  std::cout << *i << std::endl; 
//  mtx->unlock(); 
//} 

/*
The application behaves exactly like the previous one. The only difference 
is the mutex object which is now stored directly in the shared memory using 
the construct() or find_or_construct() method of the 
boost::interprocess::managed_shared_memory class.

Besides the lock() method, both boost::interprocess::named_mutex and 
boost::interprocess::interprocess_mutex provide the try_lock() and 
timed_lock() methods. They behave exactly like their counterparts provided 
by the mutex classes of Boost.Thread.
*/

/*
In case recursive mutex objects are required, Boost.Interprocess offers the 
two classes boost::interprocess::named_recursive_mutex and 
boost::interprocess::interprocess_recursive_mutex.

While mutex objects guarantee exclusive access to a shared resource, 
conditional variables control who has to have exclusive access at what 
time. In general, the conditional variables provided by Boost.Interprocess 
work the same way as the ones provided by Boost.Thread. They also have very 
similar interfaces which makes users of Boost.Thread feel immediately at 
home when using these variables in Boost.Interprocess.
*/

#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/sync/named_mutex.hpp> 
#include <boost/interprocess/sync/named_condition.hpp> 
#include <boost/interprocess/sync/scoped_lock.hpp> 
#include <iostream> 

int main() 
{ 
  // test!!
  boost::interprocess::shared_memory_object::remove("shm"); 
  boost::interprocess::named_mutex::remove("mtx"); 
  boost::interprocess::named_condition::remove("cnd"); 

  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024); 
  int *i = managed_shm.find_or_construct<int>("Integer")(0); 
  std::cout << *i << std::endl; 

  boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx"); 
  boost::interprocess::named_condition named_cnd(boost::interprocess::open_or_create, "cnd"); 
  boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(named_mtx); 
  while (*i < 10) 
  { 
    if (*i % 2 == 0) 
    { 
      ++(*i); 
      named_cnd.notify_all(); 
      named_cnd.wait(lock); 
    } 
    else 
    { 
      std::cout << *i << std::endl; 
      ++(*i); 
      named_cnd.notify_all(); 
      named_cnd.wait(lock); 
    } 
  } 
  named_cnd.notify_all(); 
  boost::interprocess::shared_memory_object::remove("shm"); 
  boost::interprocess::named_mutex::remove("mtx"); 
  boost::interprocess::named_condition::remove("cnd"); 
}

/*
The example uses a conditional variable of type boost::interprocess::named_condition 
defined in boost/interprocess/sync/named_condition.hpp. Since it is a named
variable, it does not need to be stored in shared memory.

The application uses a while loop to increment a variable of type int that
is stored in shared memory. While the variable is incremented with each
iteration of the loop, it will only be written to the standard output
stream with every second iteration: Only odd numbers are written.

Every time, the variable has been incremented by 1, the wait() method of
the conditional variable named_cnd is called. A so-called lock - in the
example the variable lock - is passed to this method. The lock has the same
meaning as it does in Boost.Thread: It is based on the RAII concept by
taking ownership of a mutex object inside the constructor and releasing it
inside the destructor.

The lock is created before the while loop and thus takes ownership of the
mutex object for the complete execution of the application. However, if
passed to the wait() method as an argument, it is automatically released.

Conditional variables are used to wait for a signal indicating that the
wait is now over. The synchronization is controlled by the wait() and
notify_all() methods. If an application calls the wait() method, the
ownership of the corresponding mutex object is released before it waits
until the notify_all() method is called for the same conditional variable.

If started, the application does not seem to do much: While the variable
is incremented from 0 to 1 within the while loop, the application then 
waits for a signal using the wait() method. In order to provide the signal,
the application needs to be started a second time.

The second instance of the application is going to try to take ownership
of the same mutex object before entering the while loop. This succeeds
since the first instance of the application released ownership of the
mutex object by calling wait(). Since the variable has been incremented
once, the second instance will now execute the else branch of the if
expression which will write the current value to the standard output
stream before incrementing it by 1.

Now the second instance also calls the wait() method. However, before it
does, it calls the notify_all() method which is important in order to have
the two instances cooperate correctly. The first instance is notified and
tries to take ownership of the mutex object again, which is still owned by
the second instance though. Since the second instance calls the wait()
method right after notify_all(), which automatically releases the ownership,
the first instance can take the ownership at that point.

Both instances alternate, incrementing the variable in the shared memory.
Only one instance writes the value to the standard output stream though. As
soon as the variable reaches the value 10, the while loop is finished. In
order to have the other instance not waiting for a signal forever,
notify_all() is called one more time after the loop. Before terminating,
the shared memory, the mutex object as well as the conditional variable is
destroyed.

Just like there are two types of mutex objects - an anonymous type that
must be stored in shared memory as well as a named type - there also exists
two type of conditional variables. The previous example is now rewritten
using an anonymous conditional variable instead.
*/

//#include <boost/interprocess/managed_shared_memory.hpp> 
//#include <boost/interprocess/sync/interprocess_mutex.hpp> 
//#include <boost/interprocess/sync/interprocess_condition.hpp> 
//#include <boost/interprocess/sync/scoped_lock.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  try 
//  { 
//    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024); 
//    int *i = managed_shm.find_or_construct<int>("Integer")(0); 
//	std::cout << *i << std::endl; 
//
//    boost::interprocess::interprocess_mutex *mtx = managed_shm.find_or_construct<boost::interprocess::interprocess_mutex>("mtx")(); 
//    boost::interprocess::interprocess_condition *cnd = managed_shm.find_or_construct<boost::interprocess::interprocess_condition>("cnd")(); 
//    boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(*mtx); 
//    while (*i < 10) 
//    { 
//      if (*i % 2 == 0) 
//      { 
//        ++(*i); 
//        cnd->notify_all(); 
//        cnd->wait(lock); 
//      } 
//      else 
//      { 
//        std::cout << *i << std::endl; 
//        ++(*i); 
//        cnd->notify_all(); 
//        cnd->wait(lock); 
//      } 
//    } 
//    cnd->notify_all(); 
//  } 
//  catch (...) 
//  { 
//  } 
//  boost::interprocess::shared_memory_object::remove("shm"); 
//}

/*
The application works exactly like the previous one and thus needs to be
started twice as well in order to increment the variable ten times. The
differences between the two examples are minimal. Whether anonymous or
named conditional variables are used is essentially irrelevant.

Besides mutex objects and conditional variables, Boost.Interprocess also
supports so-called semaphores and file locks. Semaphores behave similar to
conditional variables with the exception that they do not distinguish
between two states but rather are based upon a counter. File locks on the
other hand behave like mutex objects although they are not about objects
in memory but rather about files in the file system.

Just like Boost.Thread distinguishes between different types of mutex
objects and locks, Boost.Interprocess also provides several mutex objects
and locks. For example, mutex objects that not only can be owned exclusive
but also non-exclusive. This is helpful if multiple applications need to
read data simultaneously but write the data exclusively. Different classes
for locks are available to apply the RAII concept to the individual mutex
objects.
*/

/*
Please note that names should be unique unless anonymous synchronization 
objects are used. Even though mutex objects and conditional variables are
objects based on different classes, this may not necessarily hold true for
the operating system dependent interfaces prescinded by Boost.Interprocess.
In Windows, the same operating system functions are used for both mutex
objects and conditional variables. If the same name is used for both these
objects, the application will not behave correctly in Windows.
*/