/*
On today's computers there can be typically many processes found. For 
example a user might work with a spreadsheet application while listening to 
music played by a media player. At the same time the computer might be 
protected by an anti-virus program running in the background. It would be 
nice if a library for process management offered a way to detect processes 
and access them somehow.

As of today Boost.Process provides a way to access only one process: The 
very own process. It's neither possible to find out how many processes there 
are nor what their identifiers are for example. There is only a class 
boost::process::self which is used to access the very own process.

The class boost::process::self is a singleton and can't be instantiated. A 
static method get_instance() must be called which returns an object of type 
boost::process::self. This object represents the current process and can 
be used to access environment variables.
*/

//#include <boost/process.hpp> 
//#include <iostream> 
//
//using namespace boost::process; 
//
//int main() 
//{ 
//  self &s = self::get_instance(); 
//  environment env = s.get_environment(); 
//  for (environment::iterator it = env.begin(); it != env.end(); ++it) 
//    std::cout << it->first << "=" << it->second << std::endl;
//}

/*
The method get_environment() returns an object of type boost::process::environment 
which is a typedef for std::map<std::string, std::string>. The environment 
variables can then be processed using the well-known methods of std::map. 
In the sample code above they are written to the standard output stream.

As the environment variables returned by get_environment() are stored in an 
object of type boost::process::environment which is only a typedef for 
std::map adding, removing or changing values in the map does not affect 
the process' environment variables. Any changes to the process' environment 
variables for example by calling setenv() on POSIX systems and 
SetEnvironmentVariable() on Windows systems are not reflected in the map 
either. An object of type boost::process::environment is a snapshot of a 
process' environment variables - nothing more.
*/

/*
It could make sense to use another container type than std::map, e.g. 
std::unordered_map. On Windows systems however the environment variables 
are always sorted. As boost::process::environment will be used later to 
pass environment variables to a new process std::map makes sure that they 
really are sorted. As sorting is not required on POSIX systems though 
either two different definitions could be used or - if this is too confusing
- developers could define a macro to make Boost.Process use two different 
definitions. By default, Boost.Process would stick to std::map on all 
platforms though.

As Boost.Process doesn't provide classes or functions to detect other 
processes developers need to use platform-specific functions. Windows for 
example provides CreateToolhelp32Snapshot() which can be used to iterate 
over processes. Each process is described by a PROCESSENTRY32 structure 
which contains among others a process identifier. The process identifier 
could be used to instantiate boost::process::process as its constructor 
accepts a process identifier as a sole argument.
*/

#include <windows.h> 
#include <tlhelp32.h> 
#include <boost/process.hpp> 
#include <iostream> 

using namespace boost::process; 

int main() 
{ 
  HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
  if (handle == INVALID_HANDLE_VALUE) 
    return 1; 

  PROCESSENTRY32 entry; 
  entry.dwSize = sizeof(entry); 
  if (!Process32First(handle, &entry)) 
    return 2; 

  do 
  { 
    process p(entry.th32ProcessID); 
    std::cout << p.get_id() << std::endl; 
  } 
  while (Process32Next(handle, &entry)); 

  CloseHandle(handle); 
} 

/*
While boost::process::process can be initialized with th32ProcessID it 
doesn't really make much sense. There is more information available in a 
PROCESSENTRY32 structure which would be lost if a program continues to 
work with boost::process::process only. Boost.Process should better provide 
a platform-independent function to detect and iterate over processes.
*/