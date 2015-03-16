/*
	processes in a row
*/

/*
A pipeline is a special case in which two or more processes are created and
their standard input and output streams are connected. On POSIX and Windows
systems the pipe operator | is used to create a pipeline. Data written to 
the standard output stream of one program is received through the standard 
input stream of another program.
*/

/*
With Boost.Process it's possible to create a pipeline by calling 
boost::process::launch_pipeline(). This function expects a container with 
entries. An entry describes a process in the pipeline. The description 
contains the executable name, arguments and a context.
*/

/*
The class which is used to define an entry is boost::process::pipeline_entry. 
A pipeline is created by instantiating boost::process::pipeline_entry for 
every process, storing the entries in a container and passing it to 
boost::process::launch_pipeline().
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
//  context ctx; 
//  ctx.environment = self::get_environment(); 
//  std::vector<pipeline_entry> entries; 
//  std::vector<std::string> args = boost::assign::list_of("ls")("-l")("/"); 
//  entries.push_back(pipeline_entry(find_executable_in_path("ls"), args, ctx)); 
//  ctx.stdout_behavior = inherit_stream(); 
//  args = boost::assign::list_of("grep")("bin"); 
//  entries.push_back(pipeline_entry(find_executable_in_path("grep"), args, ctx)); 
//  launch_pipeline(entries); 
//}

/*
The sample code above does the same as if a user entered ls -l / | grep bin on a POSIX system.

The return type of boost::process::launch_pipeline() is boost::process::children which is a
typedef for std::vector<boost::process::child>. That means it's possible to access every child
process individually and for example wait until it exits. Instead of waiting for every child
process individually Boost.Process provides the helper function boost::process::wait_children().
Compared to wait() which is a method of boost::process::child boost::process::wait_children() is
a free-standing function.
*/

#include <boost/process.hpp> 
#include <boost/assign/list_of.hpp> 
#include <string> 
#include <vector> 
#include <iostream> 

using namespace boost::process; 

int main() 
{ 
  context ctx; 
  ctx.environment = self::get_environment(); 
  std::vector<pipeline_entry> entries; 
  std::vector<std::string> args = boost::assign::list_of("ls")("-l")("/"); 
  entries.push_back(pipeline_entry(find_executable_in_path("ls"), args, ctx)); 
  ctx.stdout_behavior = inherit_stream(); 
  args = boost::assign::list_of("grep")("bin"); 
  entries.push_back(pipeline_entry(find_executable_in_path("grep"), args, ctx)); 
  children cs = launch_pipeline(entries); 
  status s = wait_children(cs); 
  if (s.exited()) 
    std::cout << s.exit_status() << std::endl; 
} 
/*
When an object of type boost::process::children is returned by boost::process::launch_pipeline()
and forwarded to boost::process::wait_children() the function waits for every child process to
exit. The return code of every child process is evaluated. If a return code is found which is 
different from EXIT_SUCCESS it is returned by boost::process::wait_children(). If there are
more child processes to wait for boost::process::wait_children() will reap all of them. However
the return values of those child processes are ignored. boost::process::wait_children() returns
the first exit code which is not equal to EXIT_SUCCESS. The exit code is not returned directly
as an int but within an object of type boost::process::status.
*/