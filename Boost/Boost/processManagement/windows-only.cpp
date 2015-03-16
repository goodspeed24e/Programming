/*
 Better support of Unix platforms
*/

/*
It has been already mentioned in this article that on Windows systems the
class boost::process::win32_child can be used. To retrieve an object of 
boost::process::win32_child a process must be created with 
boost::process::win32_launch() though. In order to call
boost::process::win32_launch() the context argument must be based on 
boost::process::win32_context.
*/

#include <boost/process.hpp> 
#include <boost/assign/list_of.hpp> 
#include <string> 
#include <vector> 
#include <iostream> 

using namespace boost::process; 

int main() 
{ 
  std::string exec = find_executable_in_path("notepad.exe"); 
  std::vector<std::string> args = boost::assign::list_of("notepad.exe"); 
  win32_context ctx; 
  ctx.environment = self::get_environment(); 
  win32_child c = win32_launch(exec, args, ctx); 
  std::cout << c.get_handle() << std::endl; 
} 
/*
boost::process::win32_context is derived from boost::process::context. The 
only difference is that boost::process::win32_context provides another 
public property called startupinfo. It can be used to specify so-called 
startup information. Windows defines the structure STARTUPINFOA which this
property is based on. If no startup information is given this property can
be ignored and boost::process::win32_context can be treated just like
boost::process::context.

Once a Windows child process has been created a few more methods can be 
invoked. While boost::process::child defines only get_id() the class 
boost::process::win32_child defines get_handle(), get_primary_thread_handle()
and get_primary_thread_id(). And that's all - there are no really 
spectacular extensions for Windows.
*/