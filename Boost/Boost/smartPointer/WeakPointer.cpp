/*
Every smart pointer introduced so far can be used individually for different
scenarios. In contrast, a weak pointer only makes sense if used in 
conjunction with a shared pointer. It is defined as boost::weak_ptr in 
boost/weak_ptr.hpp
*/

#include <windows.h> 
#include <boost/shared_ptr.hpp> 
#include <boost/weak_ptr.hpp> 
#include <iostream> 

DWORD WINAPI reset(LPVOID p) 
{ 
  boost::shared_ptr<int> *sh = static_cast<boost::shared_ptr<int>*>(p); 
  //sh->reset(); 
  return 0; 
} 

DWORD WINAPI print(LPVOID p) 
{ 
  boost::weak_ptr<int> *w = static_cast<boost::weak_ptr<int>*>(p); 
  boost::shared_ptr<int> sh = w->lock(); 
  if (sh) 
    std::cout << *sh << std::endl; 
  return 0; 
} 

int main() 
{ 
  boost::shared_ptr<int> sh(new int(99)); 
  boost::weak_ptr<int> w(sh); 
  HANDLE threads[2]; 
  threads[0] = CreateThread(0, 0, reset, &sh, 0, 0); 
  threads[1] = CreateThread(0, 0, print, &w, 0, 0); 
  WaitForMultipleObjects(2, threads, TRUE, INFINITE); 
}

/*
A boost::weak_ptr must always be initialized with a boost::shared_ptr.

Once initialized, it basically offers only one useful method: lock(). 
It returns a boost::shared_ptr that shares ownership with the shared pointer
used to initialize the weak pointer. In case the shared pointer does not 
contain any object, the returned one is empty as well.

Weak pointers make sense whenever a function is expected to work with an 
object managed by a shared pointer, but the lifetime of the object does not
depend on the function itself. The function should only work with the object
as long as it is owned by at least one shared pointer within the program.

In case the shared pointer is reset, the object should not be kept alive due
to an additional shared pointer inside the corresponding function.

The above example creates two threads inside main() using functions provided
by the Windows API. Thus, the example only compiles and executes under the 
Windows platform.

The first thread executes the function reset() that receives the address of 
a shared pointer. The second thread executes the function print() which 
contains the address of a weak pointer. This weak pointer has been previously
initialized with the shared pointer.

Once the application is launched, both reset() and print() are executed at 
the same time. However, the order of execution cannot be predicted. This 
leads to the potential issue of reset() destroying the object while it is
being accessed by print() at the same time.

The weak pointer solves this issue as follows: Invoking lock() returns a 
shared pointer which points to a valid object in case it exists at the time
of the call. If not, the shared pointer is set to 0 and thus equivalent t
o a standard null pointer.

The weak pointer itself does not have any impact on the lifetime of an object.
In order to safely access the object within the print() function nonetheless,
lock() returns a shared pointer. This guarantees that - even if the object
is attempted to be released by a different thread - it continues to exist
thanks to the returned shared pointer.
*/