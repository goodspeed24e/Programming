/*
The previous section introduced the class boost::interprocess::shared_memory_object 
used to create and manage a shared memory. In practice, this class is hardly 
used though since it requires to read and write individual bytes from and to 
the shared memory. Conceptually, C++ rather promotes creating objects of 
classes and hiding the specifics of where and how they are stored in memory.

Boost.Interprocess provides a concept named managed shared memory through 
the boost::interprocess::managed_shared_memory class defined in boost/interprocess/managed_shared_memory.hpp. 

With the aid of this class, objects can be instantiated in a way that the 
memory required by the individual object is located in shared memory making 
each object automatically available to other applications accessing the 
same shared memory.
*/

//#include <boost/interprocess/managed_shared_memory.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::interprocess::shared_memory_object::remove("Highscore"); 
//
//  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
//  int *i = managed_shm.construct<int>("Integer")(99); 
//  std::cout << *i << std::endl; 
//
//  std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer"); 
//  if (p.first) 
//    std::cout << *p.first << std::endl; 
//} 

/*
The above example opens the shared memory named Highscore with a size of 
1,024 bytes. In case it does not exist, it will be automatically created.

While in a regular shared memory individual bytes are being directly 
accessed in order to read or write data, managed shared memory uses methods 
such as construct(). This method expects a data type as its template 
argument - in the example type int is declared. The method itself expects a 
name to denote the object created in the managed shared memory. The example 
uses the name 'Integer'.

Since construct() returns a proxy object, arguments can be passed to it in 
order to initialize the created object. The syntax looks like a call to a 
constructor. This ensures that objects not only can be created in a managed 
shared memory but also can be initialized as desired.

To access a particular object in the managed shared memory, the find() 
method is used. By passing the name of the object to find, find() returns
either a pointer to the particular object or 0 in case no object with the 
given name was found.
*/

/*
As seen in the above example, find() actually returns an object of type 
std::pair. The pointer to the object is provided as the first property. What 
is provided as the second property though?
*/

//#include <boost/interprocess/managed_shared_memory.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::interprocess::shared_memory_object::remove("Highscore"); 
//  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
//  int *i = managed_shm.construct<int>("Integer")[10](99); 
//  std::cout << *i << std::endl; 
//  std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer"); 
//  if (p.first) 
//  { 
//    std::cout << *p.first << std::endl; 
//    std::cout << p.second << std::endl; 
//  } 
//}

/*
This time, an array for ten elements of type int is created by providing 
the value 10 enclosed by square brackets after the call to construct(). 
The same 10 is written to the standard output stream using the second 
property. Using this property, objects returned by the find() method can be 
distinguished between single objects and array objects. For the former, 
second is set to 1 while for the latter it will specify the number of 
elements in the array.

Please note that all ten elements within the array are initialized with the 
value 99. It is not possible to initialize individual elements with 
different values.
*/

/*
construct() will fail if there exists an object with the given name in the 
managed shared memory already. In this case, construct() returns 0. If the 
existing object should be reused in case it already exists, the 
find_or_construct() method can be used which returns a pointer to the 
existing object if found. In this case, no initialization happens.
*/

/*
There are other cases that cause construct() to fail as shown in the 
following example.
*/

//#include <boost/interprocess/managed_shared_memory.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  try 
//  { 
//    boost::interprocess::shared_memory_object::remove("Highscore"); 
//    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
//    int *i = managed_shm.construct<int>("Integer")[4096](99); 
//  } 
//  catch (boost::interprocess::bad_alloc &ex) 
//  { 
//    std::cerr << ex.what() << std::endl; 
//  } 
//}

/*
The application tries to create an array of type int containing 4,096 elements. 
The managed shared memory, however, only contains 1,024 bytes. Therefore, 
the requested memory cannot be provided by the shared memory causing an 
exception of type boost::interprocess::bad_alloc to be thrown.

Once objects have been created in a managed shared memory, they can be 
deleted using the destroy() method.
*/

//#include <boost/interprocess/managed_shared_memory.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::interprocess::shared_memory_object::remove("Highscore"); 
//  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
//  int *i = managed_shm.find_or_construct<int>("Integer")(99); 
//  std::cout << *i << std::endl; 
//  managed_shm.destroy<int>("Integer"); 
//
//  std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer"); 
//  std::cout << p.first << std::endl; 
//}

/*
As its single argument, the name of the object to be deleted is passed to 
destroy(). If required, the return value of type bool can be checked to 
verify whether the given object has been found and deleted successfully. 
Since an object will always be deleted if found, the return value of false 
indicates that no object with the given name was found.
*/

/*
Besides destroy(), another method named destroy_ptr() is provided which can 
be used to pass a pointer to an object in the managed shared memory. It also 
can be used to delete arrays.

Since managed shared memory makes it fairly easy to store objects shared 
between different applications, it seems natural to use the containers 
from the C++ Standard Template Library as well. These containers allocate 
required memory independently using new though. In order to use these 
containers in managed shared memory, they need to be advised to rather 
allocate the memory in the shared memory.
*/

/*
Unfortunately, many implementations of the C++ Standard Template Library 
are not flexible enough to use the provided containers such as std::string 
or std::list together with Boost.Interprocess. One example for such an 
implementation is the one that ships with Microsoft Visual Studio 2008.

In order to allow developers the possibility to use the containers known 
from the C++ standard, Boost.Interprocess offers more flexible 
implementations of them in the namespace boost::interprocess. For example, 
boost::interprocess::string acts exactly as its C++ counterpart 
std::string with the advantage that its objects can be safely stored in a 
managed shared memory.
*/

//#include <boost/interprocess/managed_shared_memory.hpp> 
//#include <boost/interprocess/allocators/allocator.hpp> 
//#include <boost/interprocess/containers/string.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::interprocess::shared_memory_object::remove("Highscore"); 
//  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
//  typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator; 
//  typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> string; 
//  string *s = managed_shm.find_or_construct<string>("String")("Hello!", managed_shm.get_segment_manager()); 
//  s->insert(5, ", world"); 
//  std::cout << *s << std::endl; 
//}

/*
To create a string that will allocate required memory within the same 
managed shared memory it resides, a corresponding data type must be defined 
in order to use a different allocator, provided by Boost.Interprocess, 
rather than the default allocator provided by the C++ standard.

For this purpose, Boost.Interprocess offers the class boost::interprocess::allocator 
defined in boost/interprocess/allocators/allocator.hpp. Using this class, an 
allocator can be created that internally uses the so-called segment manager 
of the managed shared memory. The segment manager is responsible for the 
management of the memory within a managed shared memory. Using the newly 
created allocator, a corresponding data type for the string can be defined. 
As indicated above, it uses boost::interprocess::basic_string rather than 
std::basic_string. The new data type - in the example simply named string - 
is based on boost::interprocess::basic_string and accesses the segment 
manager via its allocator. In order to let the particular instance of 
string, created by a call to find_or_construct(), know which segment 
manager it should access, a pointer to the corresponding segment manager is 
passed as the second argument to the constructor.
*/

/*
Alongside boost::interprocess::string, Boost.Interprocess provides 
implementations for many other containers known from the C++ standard. For 
example, boost::interprocess::vector and boost::interprocess::map defined 
in boost/interprocess/containers/vector.hpp and 
boost/interprocess/containers/map.hpp, respectively.

Whenever the same managed shared memory is accessed from different 
applications, operations such as creating, finding and destroying objects 
are automatically synchronized. If two applications try to create objects 
with different names in the managed shared memory, the access is serialized 
accordingly. In order to execute multiple operations at once without being 
interrupted by operations from a different application, the atomic_func() 
method can be used.
*/

#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/bind.hpp> 
#include <iostream> 

void construct_objects(boost::interprocess::managed_shared_memory &managed_shm) 
{ 
  managed_shm.construct<int>("Integer")(99); 
  managed_shm.construct<float>("Float")(3.14); 
} 

int main() 
{ 
  // test! to remove boost::interprocess::shared_memory_object::remove("Highscore");  	
  boost::interprocess::shared_memory_object::remove("Highscore"); 
  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
  managed_shm.atomic_func(boost::bind(construct_objects, boost::ref(managed_shm))); 
  std::cout << *managed_shm.find<int>("Integer").first << std::endl; 
  std::cout << *managed_shm.find<float>("Float").first << std::endl; 
}

/*
atomic_func() expects a function, taking no arguments and not returning any 
value, as its single argument. The passed function will be called in a 
fashion that ensures exclusive access to the managed shared memory - but 
only for operations such as creating, finding or deleting objects. If 
another application has a pointer to an object within the managed shared 
memory, it can access and modify this object using its pointer.

Boost.Interprocess can also be used to synchronize object access. Since 
Boost.Interprocess does not know who can access the individual objects at 
what point in time, the synchronization needs to be explicitly stated. The 
classes provided for synchronization are introduced in the following 
section.
*/
