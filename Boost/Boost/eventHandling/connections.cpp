/*
Functions can be managed with the aid of the connect() and disconnect() 
methods provided by boost::signal. Due to connect() returning a value of 
type boost::signals::connection, they can be managed differently as well.
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//
//void func() 
//{ 
//  std::cout << "Hello, world!" << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::signal<void ()> s; 
//  boost::signals::connection c = s.connect(func); 
//  s(); 
//  c.disconnect(); 
//} 

/*
The disconnect() method of boost::signal requires a function pointer being 
passed which can be avoided by calling the disconnect() method on the 
boost::signals::connection object directly.
*/

/*
In addition to the disconnect() method, boost::signals::connection also 
provides methods such as block() and unblock().
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//
//void func() 
//{ 
//  std::cout << "Hello, world!" << std::endl; 
//} 
//
//int main() 
//{ 
//  boost::signal<void ()> s; 
//  boost::signals::connection c = s.connect(func); 
//  c.block(); 
//  s(); 
//  c.unblock(); 
//  s(); 
//}

/*
The above program executes func() exactly once. Even though the signal s is
triggered twice, func() is not called for the first trigger since the 
connection c has actually been blocked by a call to block(). Since 
unblock() is called before the second trigger, func() is now executed 
correctly.
*/

/*
Besides boost::signals::connection, a class named boost::signals::scoped_connection
is offered that releases the connection during destruction automatically.
*/

//#include <boost/signal.hpp> 
//#include <iostream> 
//
//void func()
//{
//  std::cout << "Hello, world!" << std::endl;
//}
//
//int main()
//{
//  boost::signal<void ()> s;
//  {
//    boost::signals::scoped_connection c = s.connect(func);
//  }
//  s();
//}

/*
Since the connection object c is destroyed before the signal is triggered,
func() is not being called.

boost::signals::scoped_connection is actually derived from boost::signals::connection 
and thus offers the same methods. The only difference is the automatic
release of the connection during destruction of boost::signals::scoped_connection.

While boost::signals::scoped_connection certainly makes it easier to 
automatically release connections, objects of this type still need to be
managed. It would be nice if connections could be automatically released 
in other cases as well without having the need to actually manage these
objects.
*/

//#include <boost/signal.hpp> 
//#include <boost/bind.hpp> 
//#include <iostream> 
//#include <memory> 
//
//class world 
//{ 
//  public: 
//    void hello() const 
//    { 
//      std::cout << "Hello, world!" << std::endl; 
//    } 
//}; 
//
//int main() 
//{ 
//  boost::signal<void ()> s; 
//  { 
//    std::auto_ptr<world> w(new world()); 
//    s.connect(boost::bind(&world::hello, w.get())); 
//  } 
//  std::cout << s.num_slots() << std::endl; 
//  s(); 
//}

/*
The above program associates the method of an object with a signal by using
Boost.Bind. The object is destroyed before the signal is triggered which 
creates an issue. Opposed to passing the actual object w, only a pointer
has been passed to boost::bind() instead. By the time s() is actually 
called, the object referenced by the pointer does no longer exist.

It is possible to modify the program so that the connection is automatically
released once the object w is destroyed.
*/

#include <boost/signal.hpp> 
#include <boost/bind.hpp> 
#include <iostream> 
#include <memory> 

class world : 
  public boost::signals::trackable 
{ 
  public: 
    void hello() const 
    { 
      std::cout << "Hello, world!" << std::endl; 
    } 
}; 

int main() 
{ 
  boost::signal<void ()> s; 
  { 
    std::auto_ptr<world> w(new world()); 
    s.connect(boost::bind(&world::hello, w.get())); 
  } 
  std::cout << s.num_slots() << std::endl; 
  s(); 
}

/*
If executed now, num_slots() actually returns 0 to make sure that no 
method is tried to be called on an already destroyed object. The only 
change necessary was to derive the world class from boost::signals::trackable. 

Whenever pointers to objects instead of object copies are used to associate
functions with signals, boost::signals::trackable can simplify the 
management of the connections considerably.
*/