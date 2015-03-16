/*
 kill a process
*/

/*
It is possible to terminate another process by invoking terminate() which is
defined by boost::process::process. Of course it's not possible to 
terminate an arbitrary process. Operating systems check access rights 
before they allow a process to terminate another one. As Boost.Process 
currently doesn't provide any means to access any processes but only child 
processes terminate() will always work for now.
*/

/*
On POSIX systems terminate() is implemented by sending the signal SIGTERM.
As processes are allowed to ignore SIGTERM it is possible to make terminate() 
send SIGKILL which can't be ignored. If the sole argument of terminate() is
set to true - the default value is false - SIGKILL is sent.
*/

#include <boost/process.hpp> 
#include <boost/thread.hpp> 
#include <boost/assign/list_of.hpp> 
#include <string> 
#include <vector> 

using namespace boost::process; 

int main() 
{ 
  std::string exec = find_executable_in_path("notepad.exe"); 
  std::vector<std::string> args = boost::assign::list_of("notepad.exe"); 
  context ctx; 
  ctx.environment = self::get_environment(); 
  child c = launch(exec, args, ctx); 
  boost::this_thread::sleep(boost::posix_time::seconds(3)); 
  c.terminate(); 
}

/*
On Windows terminate() calls TerminateProcess(). The parameter is ignored 
as TerminateProcess() always causes another process to exit.

As a side note, it is not really recommended to use terminate(). It forces 
another process to exit no matter in what state it is. Calling terminate() 
should be really a last resort if nothing else works and the other process 
must exit as soon as possible.
*/