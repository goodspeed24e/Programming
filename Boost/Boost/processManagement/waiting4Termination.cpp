/*
 spare a minute
*/

/*
When terminate() is called the respective process is terminated immediately.
However if a process wants to wait for another process to exit wait() can be
called. While terminate() is defined by boost::process::process wait() 
belongs to boost::process::child. That means a process can only wait for 
child processes to exit. This is not really reasonable and should be changed.

Another problem with wait() is that it is a blocking function: wait() only 
returns if the process has exited. There is currently no support to wait 
asynchronously. Again this is something which should be changed.
*/

#include <boost/process.hpp> 
#include <boost/assign/list_of.hpp> 
#include <string> 
#include <vector> 
#include <iostream> 

using namespace boost::process; 

int main() 
{ 
  std::string exec = find_executable_in_path("hostname"); 
  std::vector<std::string> args = boost::assign::list_of("hostname"); 
  context ctx; 
  ctx.environment = self::get_environment(); 
  child c = launch(exec, args, ctx); 
  status s = c.wait(); 
  if (s.exited()) 
    std::cout << s.exit_status() << std::endl; 
}

/*
When a process exits wait() returns an object of type boost::process::status.
This class provides methods to find out how a process exited. The method 
exited() can be called to detect if the process exited gracefully. Only if 
it returns true exit_status() can be called which returns the exit code.
*/

//#include <boost/process.hpp> 
//#include <boost/assign/list_of.hpp> 
//#include <string> 
//#include <vector> 
//#include <iostream> 
//
//using namespace boost::process; 
//
//int main() 
//{ 
//  std::string exec = find_executable_in_path("hostname"); 
//  std::vector<std::string> args = boost::assign::list_of("hostname"); 
//  context ctx; 
//  ctx.environment = self::get_environment(); 
//  child c = launch(exec, args, ctx); 
//  posix_status s = c.wait(); 
//  if (s.exited()) 
//    std::cout << s.exit_status() << std::endl; 
//  if (s.signaled()) 
//    std::cout << s.term_signal() << std::endl; 
//} 

/*
POSIX systems provide more data when a process exited. That's why 
Boost.Process defines another class boost::process::posix_status which can 
be instantiated with an object of type boost::process::status. For example 
it defines a method signaled() which returns true if the process exited 
because it received an external signal. With term_signal() this signal can 
be fetched.

If a process spawns a child process and doesn't care about it it doesn't 
need to wait for the child process to exit. However on POSIX systems if the 
child process exits and the parent process is still running the child 
process becomes a zombie process. The operating system still saves data 
about the child process like its return code. This data is saved until the
parent process collects it with wait() or exits itself. That's why it is 
recommended to always reap child processes by calling wait(). That's not
easy if several child processes have been created as wait() blocks. Again 
this is another area where Boost.Process deserves to be improved. As 
SIGCHLD is sent to a parent process whenver a child process exits and 
becomes a zombie process Boost.Process could setup an I/O object for 
handling SIGCHLD signals asynchronously.

There is a similar problem on Windows. Windows cleans up resources only 
when all handles are closed. As objects of type boost::process::child store
a handle to another process Windows can't clean up resources even if the 
other process has exited - and even if wait() has been called and returned!
The object must be destroyed as only the destructor of boost::process::child 
closes the handle.
*/