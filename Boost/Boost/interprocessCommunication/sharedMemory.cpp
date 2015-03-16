/*
Shared memory is typically the fastest form of interprocess communication. 
It provides a memory area that is shared between different applications. 
One application can write data to the area while another application can 
read the same data accordingly.

Such a memory area is represented in Boost.Interprocess by the 
boost::interprocess::shared_memory_object class. To use this class, the 
boost/interprocess/shared_memory_object.hpp header file needs to be 
included.
*/

//#include <boost/interprocess/shared_memory_object.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write); 
//  shdmem.truncate(1024);  // bytes unit
//  std::cout << shdmem.get_name() << std::endl; 
//  boost::interprocess::offset_t size; 
//  if (shdmem.get_size(size)) 
//    std::cout << size << std::endl; 
//} 

/*
The constructor of boost::interprocess::shared_memory_object expects three 
parameters. 

The first one specifies whether the shared memory should be created or just 
opened. The above example actually does it either way: using boost::interprocess::open_or_create, 
the shared memory is opened if it already exists, otherwise it will be created.
Opening an existing shared memory assumes that it has been created before. 
To uniquely identify a shared memory, a name is being assigned accordingly. 

The second parameter passed to the constructor of boost::interprocess::shared_memory_object 
specifies that name.

The third and last parameter determines how an application can access the 
shared memory. The shown application can both read from and write to the 
shared memory due to the boost::interprocess::read_write value.
*/

/*
After creating an object of type boost::interprocess::shared_memory_object, 
a corresponding shared memory exists within the operating system. The size 
of this memory area, however, is initially 0. In order to utilize the area, 
the truncate() method needs to be called, passing the requested size of the 
shared memory in bytes. For the above example, the shared memory provides 
space for 1,024 bytes.

Please note that the truncate() method can only be called if the shared 
memory has been opened with boost::interprocess::read_write. If not, an 
exception of type boost::interprocess::interprocess_exception will be thrown.

In order to adjust the size of the shared memory, the truncate() method can 
be called repeatedly.

After creating a shared memory, methods such as get_name() and get_size() 
can be used to query the name and the size, respectively.
/*

/*
Since shared memory is used to exchange data between different applications,
each application needs to map the shared memory into its address space 
which is done via the boost::interprocess::mapped_region class.

It may come as a surprise that two classes are actually used in order to 
access the shared memory. However, the boost::interprocess::mapped_region 
class can also be used to map different objects into the address space of a 
particular application. For example, Boost.Interprocess provides a 
boost::interprocess::file_mapping class which essentially represents a 
shared memory for a particular file. Thus, an object of type 
boost::interprocess::file_mapping corresponds to a file. Data written to 
such an object is automatically saved in the associated physical file. Since 
boost::interprocess::file_mapping does not load the file completely but 
rather maps arbitrary parts into the address space using 
boost::interprocess::mapped_region, it is possible to process files of 
several gigabytes in size that can not be completely loaded into memory on 
32-bit systems otherwise.
*/

//#include <boost/interprocess/shared_memory_object.hpp> 
//#include <boost/interprocess/mapped_region.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write); 
//  shdmem.truncate(1024); 
//
//  boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write); 
//  std::cout << std::hex << "0x" << region.get_address() << std::endl; 
//  std::cout << std::dec << region.get_size() << std::endl; 
//
//  boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only); 
//  std::cout << std::hex << "0x" << region2.get_address() << std::endl; 
//  std::cout << std::dec << region2.get_size() << std::endl; 
//}

/*
In order to use the boost::interprocess::mapped_region class, the header 
boost/interprocess/mapped_region.hpp needs to be included. An object of type 
boost::interprocess::shared_memory_object must be passed as the first 
argument to the constructor of boost::interprocess::mapped_region. 

The second argument determines whether the memory area can be accessed 
read-only or whether applications are allowed to write to it as well.

The above example creates two objects of type boost::interprocess::mapped_region: 
The shared memory named Highscore is mapped twice into the address space of 
the process. The address as well as the size of the mapped memory area is 
written to the standard output stream using the get_address() and get_size() 
methods. While get_size() returns 1024 in both cases, the return value of 
get_address() is different.
*/

/*
The following example uses the mapped memory area to write and read a number.
*/

//#include <boost/interprocess/shared_memory_object.hpp> 
//#include <boost/interprocess/mapped_region.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write); 
//  shdmem.truncate(1024); 
//
//  boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write); 
//  int *i1 = static_cast<int*>(region.get_address()); 
//  *i1 = 99; 
//
//  boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only); 
//  int *i2 = static_cast<int*>(region2.get_address()); 
//  std::cout << *i2 << std::endl; 
//}

/*
By means of region, the number 99 is written to the beginning of the shared 
memory. region2 then accesses the same location of the shared memory to 
write the number to the standard output stream. Even though region and 
region2 represent different memory areas within the process as seen by the 
return value of get_address() in the previous example, the program prints 99 
since both memory areas access the same underlying shared memory.

Usually, multiple objects of type boost::interprocess::mapped_region would 
not be used for the shared memory within the same application. There is 
actually not much sense accessing the same shared memory using two different 
memory areas. 
*/

/*
The above example is only meant for illustration purposes.

In order to delete a particular shared memory, boost::interprocess::shared_memory_object 
offers the static remove() method which takes the name of the shared memory 
to be deleted as its argument.

Boost.Interprocess kind of supports the RAII concept known from the chapter 
about smart pointers using a separate class named boost::interprocess::remove_shared_memory_on_destroy. 

Its constructor expects the name of an existing shared memory. If an object 
of this class is destroyed, the contained shared memory is automatically 
deleted within the destructor.
*/

/*
Please note that the constructor of boost::interprocess::remove_shared_memory_on_destroy 
does not create or open the shared memory. Therefore, this class is not a 
typical representative of the RAII concept.
*/

//#include <boost/interprocess/shared_memory_object.hpp> 
//#include <iostream> 
//
//int main() 
//{ 
//  bool removed = boost::interprocess::shared_memory_object::remove("Highscore"); 
//  std::cout << removed << std::endl; 
//}

/*
If remove() is not being called at all, the shared memory continues to 
exist even if the application is terminated. Whether or not the shared 
memory is deleted depends on the underlying operating system. While many 
Unix operating systems, including Linux, automatically delete a shared 
memory once the system is restarted, remove() must be called while working 
with Windows or Mac OS X. Both systems actually store the shared memory as 
a persistent file which is still available after a restart.

Windows provides a special kind of shared memory that is automatically 
deleted once the last application using it has been terminated. In order to 
use it, the boost::interprocess::windows_shared_memory class, defined in 
boost/interprocess/windows_shared_memory.hpp, is provided.
*/

#include <boost/interprocess/windows_shared_memory.hpp> 
#include <boost/interprocess/mapped_region.hpp> 
#include <iostream> 

int main() 
{ 
  boost::interprocess::windows_shared_memory shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write, 1024); 
  
  boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write); 
  int *i1 = static_cast<int*>(region.get_address()); 
  *i1 = 99; 
  boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only); 
  int *i2 = static_cast<int*>(region2.get_address()); 
  std::cout << *i2 << std::endl; 
}

/*
Please note that boost::interprocess::windows_shared_memory does not 
provide a truncate() method. Instead, the size of the shared memory needs 
to be passed as the fourth argument to the constructor.

Even though the boost::interprocess::windows_shared_memory class is not 
portable and can only be used within Windows, it is helpful while 
exchanging data between different applications that use this special kind 
of shared memory.
*/