/*
Even though Boost.Asio mainly supports network functions, adding additional 
I/O objects to perform different asynchronous operations is fairly easy. 
This section outlines the general layout of a Boost.Asio extension. While 
it is not mandatory, it provides a viable skeleton as a starting point for 
other extensions.
*/

/*
To add new asynchronous operations to Boost.Asio, three classes need to be 
implemented:

A class derived from boost::asio::basic_io_object representing the new I/O 
object. Developers using the new Boost.Asio extension will exclusively 
encounter this I/O object.

A class derived from boost::asio::io_service::service representing a 
service that is registered with the I/O service and can be accessed from 
the I/O object. The differentiation between the service and the I/O object
is important since there is only one instance of the service per I/O 
service at any given time but a service can be accessed by multiple I/O objects.

A class not derived from any other class representing the service 
implementation. Since there is only one instance of a service per I/O 
service at any given time, the service creates an instance of its 
implementation for every I/O object. This instance manages the internal 
data pertinent to the corresponding I/O object.
*/

/*
Instead of just providing the skeleton, the Boost.Asio extension developed 
in this section is going to resemble the available boost::asio::deadline_timer
object. The difference between the two is that the period for the timer is 
being passed as an argument to the wait() or async_wait() method instead of 
the constructor.
*/

#include <boost/asio.hpp> 
#include <cstddef> 

template <typename Service> 
class basic_timer 
  : public boost::asio::basic_io_object<Service> 
{ 
  public: 
    explicit basic_timer(boost::asio::io_service &io_service) 
      : boost::asio::basic_io_object<Service>(io_service) 
    { 
    } 

    void wait(std::size_t seconds) 
    { 
      return this->service.wait(this->implementation, seconds); 
    } 

    template <typename Handler> 
    void async_wait(std::size_t seconds, Handler handler) 
    { 
      this->service.async_wait(this->implementation, seconds, handler); 
    } 
}

/*
Every I/O object is usually implemented as a template class that is 
required to be instantiated with a service - typically with the service 
specifically developed for this I/O object. Whenever an I/O object is 
instantiated, the service is automatically registered with the I/O service 
by the parent class boost::asio::basic_io_object, unless it was already 
registered previously. This ensures that services used by any I/O object 
will only be registered once per I/O service.

The corresponding service is accessible within the I/O object via the 
service reference and is typically accessed to forward method calls to the 
service. Since services need to store data for every I/O object, an 
instance is automatically created for every I/O object using the service. 
This again happens with the aid of the parent class boost::asio::basic_io_object. 

The actual service implementation is passed as an argument to any method 
call to allow the service to specifically know which I/O object initiated 
the call. The service implementation is accessible via the implementation 
property.
*/

/*
In general, any I/O object is relatively simple: While the installation of 
the service as well as the creation of a service implementation is done by 
the parent class boost::asio::basic_io_object, method calls are simply 
forwarded to the corresponding service; passing the actual service 
implementation of the I/O object as an argument.
*/

#include <boost/asio.hpp> 
#include <boost/thread.hpp> 
#include <boost/bind.hpp> 
#include <boost/scoped_ptr.hpp> 
#include <boost/shared_ptr.hpp> 
#include <boost/weak_ptr.hpp> 
#include <boost/system/error_code.hpp> 

template <typename TimerImplementation = timer_impl> 
class basic_timer_service 
  : public boost::asio::io_service::service 
{ 
  public: 
    static boost::asio::io_service::id id; 

    explicit basic_timer_service(boost::asio::io_service &io_service) 
      : boost::asio::io_service::service(io_service), 
      async_work_(new boost::asio::io_service::work(async_io_service_)), 
      async_thread_(boost::bind(&boost::asio::io_service::run, &async_io_service_)) 
    { 
    } 

    ~basic_timer_service() 
    { 
      async_work_.reset(); 
      async_io_service_.stop(); 
      async_thread_.join(); 
    } 

    typedef boost::shared_ptr<TimerImplementation> implementation_type; 

    void construct(implementation_type &impl) 
    { 
      impl.reset(new TimerImplementation()); 
    } 

    void destroy(implementation_type &impl) 
    { 
      impl->destroy(); 
      impl.reset(); 
    } 

    void wait(implementation_type &impl, std::size_t seconds) 
    { 
      boost::system::error_code ec; 
      impl->wait(seconds, ec); 
      boost::asio::detail::throw_error(ec); 
    } 

    template <typename Handler> 
    class wait_operation 
    { 
      public: 
        wait_operation(implementation_type &impl, boost::asio::io_service &io_service, std::size_t seconds, Handler handler) 
          : impl_(impl), 
          io_service_(io_service), 
          work_(io_service), 
          seconds_(seconds), 
          handler_(handler) 
        { 
        } 

        void operator()() const 
        { 
          implementation_type impl = impl_.lock(); 
          if (impl) 
          { 
              boost::system::error_code ec; 
              impl->wait(seconds_, ec); 
              this->io_service_.post(boost::asio::detail::bind_handler(handler_, ec)); 
          } 
          else 
          { 
              this->io_service_.post(boost::asio::detail::bind_handler(handler_, boost::asio::error::operation_aborted)); 
          } 
      } 

      private: 
        boost::weak_ptr<TimerImplementation> impl_; 
        boost::asio::io_service &io_service_; 
        boost::asio::io_service::work work_; 
        std::size_t seconds_; 
        Handler handler_; 
    }; 

    template <typename Handler> 
    void async_wait(implementation_type &impl, std::size_t seconds, Handler handler) 
    { 
      this->async_io_service_.post(wait_operation<Handler>(impl, this->get_io_service(), seconds, handler)); 
    } 

  private: 
    void shutdown_service() 
    { 
    } 

    boost::asio::io_service async_io_service_; 
    boost::scoped_ptr<boost::asio::io_service::work> async_work_; 
    boost::thread async_thread_; 
}; 

template <typename TimerImplementation> 
boost::asio::io_service::id basic_timer_service<TimerImplementation>::id;

/*
In order to be integrated with Boost.Asio, a service must fulfill a couple 
of requirements:

It needs to be derived from boost::asio::io_service::service. The 
constructor must expect a reference to an I/O service which is passed to 
the constructor of boost::asio::io_service::service accordingly.

Any service must contain a static public property id of type boost::asio::io_service::id. 
Services are identified using this property within the I/O service.

Two public methods named construct() and destruct(), both expecting an 
argument of type implementation_type, must be defined. implementation_type 
is typically a type definition for the service implementation. As shown in 
the above example, a boost::shared_ptr object can be used to easily 
instantiate a service implementation in construct() and to destruct it in 
destruct() accordingly. Since both methods are automatically being called 
whenever an I/O object is created or destroyed, a service can create and 
destroy service implementations for each I/O object using construct() and 
destruct(), respectively.

A method named shutdown_service() must be defined; however, it can be 
private. For common Boost.Asio extensions, this is usually an empty method. 
It is only being used by services that are more tightly integrated with 
Boost.Asio. Nonetheless, the method must be present in order to compile the 
extension successfully.

In order to forward method calls to the corresponding service, methods for 
forwarding need to be defined for the I/O object accordingly. These methods 
are typically named similar to the methods of the I/O object itself, e.g. wait() and async_wait() in the above example. While synchronous methods such as wait() solely access the service implementation to call a blocking method, the trick for asynchronous operations like async_wait() is to call the blocking method within a thread.

Using the asynchronous operations with the help of a thread is usually done 
by accessing a new I/O service. The above example contains a property named 
async_io_service_ of type boost::asio::io_service. The run() method of this 
I/O service is started within its own thread created with async_thread_ of 
type boost::thread inside the constructor of the service. The third property 
async_work_ of type boost::scoped_ptr<boost::asio::io_service::work> is 
required to avoid the run() method from returning immediately. This could 
otherwise happen since there are no outstanding asynchronous operations at 
creation. Creating an object of type boost::asio::io_service::work and 
binding it to the I/O service, which also happens inside the service 
constructor, prevents the run() method from returning immediately.
*/

/*
A service could also be implemented without accessing its own I/O service - 
a single thread would be sufficient. The reason for using a new I/O service
for any additional thread is quite simple: Threads can communicate fairly 
easy with each other using the I/O service. In the example, async_wait() 
creates a function object of type wait_operation and passes it to the 
internal I/O service via the post() method. The overloaded operator()() of 
this function object is then called inside the thread used to execute the 
run() method for the internal I/O service. post() offers a simple way of 
executing a function object within a different thread.

The overloaded operator()() operator of wait_operation essentially performs 
the same work as the wait() method: Calling the blocking wait() method of 
the service implementation. There is, however, the possibility that the I/O 
object, including its service implementation, is destroyed while the thread 
executes the operator()() operator. If the service implementation is 
destroyed in destruct(), the operator()() operator should no longer access 
it. This is prevented by using a weak pointer known from the first chapter: 
The weak pointer impl_ returns a shared pointer to the service 
implementation if it still exists when lock() is called, otherwise it will 
return 0. In that case, operator()() does not access the service 
implementation but rather calls the handler with an error of 
boost::asio::error::operation_aborted.
*/

#include <boost/system/error_code.hpp> 
#include <cstddef> 
#include <windows.h> 

class timer_impl 
{ 
  public: 
    timer_impl() 
      : handle_(CreateEvent(NULL, FALSE, FALSE, NULL)) 
    { 
    } 

    ~timer_impl() 
    { 
      CloseHandle(handle_); 
    } 

    void destroy() 
    { 
      SetEvent(handle_); 
    } 

    void wait(std::size_t seconds, boost::system::error_code &ec) 
    { 
      DWORD res = WaitForSingleObject(handle_, seconds * 1000); 
      if (res == WAIT_OBJECT_0) 
        ec = boost::asio::error::operation_aborted; 
      else 
        ec = boost::system::error_code(); 
    } 

private: 
    HANDLE handle_; 
};

/*
The service implementation timer_impl uses Windows API functions and can 
only be compiled and used in Windows. Its purpose is rather to illustrate a
potential implementation.

timer_impl exhibits two essential methods: wait() is called to wait for one
or more seconds. destroy() is used to cancel a wait operation which is 
mandatory since the wait() method is called inside its own thread for 
asynchronous operations. If the I/O object, including its service 
implementation, is destroyed, the blocking wait() method should be
canceled as soon as possible which is done using destroy().

This Boost.Asio extension can be used as follows.
*/

#include <boost/asio.hpp> 
#include <iostream> 
#include "basic_timer.hpp" 
#include "timer_impl.hpp" 
#include "basic_timer_service.hpp" 

void wait_handler(const boost::system::error_code &ec) 
{ 
  std::cout << "5 s." << std::endl; 
} 

typedef basic_timer<basic_timer_service<> > timer; 

int main() 
{ 
  boost::asio::io_service io_service; 
  timer t(io_service); 
  t.async_wait(5, wait_handler); 
  io_service.run(); 
}
/*
Compared to the example application in the beginning of this chapter, this 
Boost.Asio extension is used similarly to boost::asio::deadline_timer. In 
practice, boost::asio::deadline_timer should be preferred since it is 
already integrated with Boost.Asio. The sole purpose of this extension was 
to show how Boost.Asio can be extended with new asynchronous operations.

Directory Monitor is a real-world example of a Boost.Asio extension that 
provides an I/O object able to monitor directories. If a file inside a 
monitored directory is created, modified or deleted, a handler is called 
accordingly. The current version supports both Windows and Linux 
(Kernel version 2.6.13 or higher).
*/