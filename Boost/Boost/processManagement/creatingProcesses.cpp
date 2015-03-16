/*
While Boost.Process doesn't really offer much when it comes to accessing 
other processes it is much better in creating processes. There are three 
functions provided which are used to launch child processes:

boost::process::launch() expects an executable name (as std::string), arguments 
to pass to the executable (as std::vector<std::string>) and a context the 
executable should be started with and run in (as boost::process::context).

boost::process::launch_shell() is used if a string contains the executable 
name and arguments. Instead of separating the executable name and arguments 
they are passed as one std::string. boost::process::launch_shell() also 
expects a context as another parameter (again as boost::process::context).

As it is possible to start several processes and redirect their input and 
output streams the function boost::process::launch_pipeline() is provided 
to start and connect two or more processes with pipes. This function 
expects a collection of entries which describe the processes.
*/
/*
All three functions are really templates - after all Boost.Process tries to 
support concepts which can be implemented as different types. The idea is 
to pass for example a string of another type to boost::process::launch() to
specify the executable name. In practice it won't be easy to use other 
types though. The current implementation of boost::process::launch() for 
example invokes size() and c_str(). If the string type doesn't provide 
these methods compilation will fail. Boost.Process either has to specify
precisely the concept of an executable name or give it up. Developers 
shouldn't be required to study the implementation of Boost.Process. As 
the implementation can also change any time code might break which worked 
before.
*/

/*
While C++ standard types are used to specify the executable name and 
arguments the context parameter is based on a class boost::process::context.
The class deserves some more explanation.

An object of type boost::process::context contains data which describes 
how an executable is started and what its runtime environment will look 
like. The class boost::process::context defines several public properties:
work_directory is the work directory the executable is started in. By 
default, the work directory is set to the current directory.

environment contains the environment variables for the new process. By 
default, no environment variables are defined. For executables linked 
against shared libraries it is typically required to define at least the 
environment variable PATH. Otherwise locating and loading required shared 
libraries fails.
*/

/*
stdin_behavior specifies the behavior of the standard input stream.
stdout_behavior specifies the behavior of the standard output stream.
stderr_behavior specifies the behavior of the standard error stream.
*/
/*
While work directory and environment variables are well-known concepts 
supported by all operating systems Boost.Process provides three settings to 
specify the behavior of the standard streams. By default, when a new 
process is created all standard streams are closed. Thus the new process 
can't read data from stdin and can't write data to stdout and stderr.

Please note that this behavior is different from the default behavior on 
POSIX systems. When fork() is used to create a new process the child 
process inherits all file descriptors from the parent process. The standard 
streams are not automatically closed.

On Windows when CreateProcess() is used the behavior of the standard 
streams is either explicitly specified by the parent process or the 
streams are automatically bound to the keyboard buffer and the console's 
window buffer. There is no default behavior.

If a program doesn't use the standard streams - e.g. because it is an 
application with a graphical user interface - the stream behaviors can be 
ignored. This makes it rather easy to launch such a program.
*/

//#include <boost/process.hpp> 
//#include <boost/assign/list_of.hpp> 
//#include <string> 
//#include <vector> 
//
//using namespace boost::process; 
//
//int main() 
//{ 
//  std::string exec = find_executable_in_path("notepad.exe"); 
//  std::vector<std::string> args = boost::assign::list_of("notepad.exe"); 
//  context ctx; 
//  ctx.environment = self::get_environment(); 
//  launch(exec, args, ctx); 
//}

/*
In the code sample above the standard Windows editor Notepad is launched. 
The executable is called notepad.exe. Now it is very important to refer to 
the executable with an absolute path - on all platforms including POSIX 
systems. The absolute path for Notepad is typically C:\Windows\System32\notepad.exe. 

Boost.Process provides a helper function boost::process::find_executable_in_path() though 
which searches for an executable and generates an absolute path. 
boost::process::find_executable_in_path() searches the directories of the 
environment variable PATH. If PATH hasn't been set or the executable isn't 
found in the directories PATH is set to boost::process::find_executable_in_path() 
throws boost::filesystem::filesystem_error.
*/

/*
Another important requirement is to always pass at least one argument to 
the executable. This must be the name of the executable itself. Whether it 
contains an extension like exe doesn't really matter - not to 
Boost.Process at least. You can also pass another string than the executable
name. The string is forwarded to the program. So it really depends on the 
program if and how it is processed. For Boost.Process it's only important 
that at least one argument has been set.
*/

/*
By the way, there is another helper function boost::process::executable_to_progname() 
which extracts the executable name from an absolute (or relative) path. For 
example it returns notepad for C:\Windows\System32\notepad.exe. The helper 
function makes it easy to specify the first argument. The current implementation
of boost::process::executable_to_progname() always strips the file extension
on Windows though.

There are no rules when it comes to specifying the context - anything goes. 
However many applications are linked against shared libraries which must be
located and loaded by the operating system. This is also true for Notepad 
which depends on DLLs in C:\Windows\System32 among others. That's why it is 
often a good idea to set the environment variable PATH at least. If all 
environment variables of the current process should be used 
boost::process::self provides a static method get_environment() which comes
handy here.
*/

/*
For programs which make use of standard streams it can be very important to
configure the context correctly. All properties stdin_behavior, 
stdout_behavior and stderr_behavior are based on boost::process::stream_behavior.

With the following helper functions instances of this class can be created
and assigned:

boost::process::capture_stream() is used to make the other end of a standard
stream available in the current process. It is then possible for the current
and the new process to communicate with each other and exchange data. On 
POSIX and Windows systems this connection is known as pipe.

boost::process::close_stream() is used to close a stream. As this is the 
default behavior this function doesn't need to be used really.

boost::process::inherit_stream() makes the child process inherit the 
standard streams of the current process. No matter if the child or current 
process writes data for example to the standard output stream - it is 
transmitted to the very same sink.

boost::process::redirect_stream_to_stdout() can be used to redirect the 
standard error stream to the standard output stream. It's a helper function 
which is not very important but might be useful for some developers.

boost::process::silence_stream() redirects the standard input stream to a 
source random data is read from and the standard output and standard error
streams to a sink which discards data written to. You use this function if
you don't care about data read from stdin and written to stdout and stderr but don't want to close the standard streams. This makes sense if you know a program expects to be able to use the standard streams and would break otherwise if they are closed.
*/

/*
When an object of type boost::process::context is passed to a function like
boost::process::launch() the standard streams of the new process are c
onfigured according to the behavior settings. If a stream is closed - the 
default behavior - nothing happens. If a stream is silenced it is redirect 
to /dev/null respectively /dev/zero on POSIX systems and redirected to NUL
on Windows systems.
*/

#include <boost/process.hpp> 
#include <boost/assign/list_of.hpp> 
#include <string> 
#include <vector> 

using namespace boost::process; 

int main() 
{ 
  std::string exec = find_executable_in_path("hostname"); 
  std::vector<std::string> args = boost::assign::list_of("hostname"); 
  context ctx; 
  ctx.environment = self::get_environment(); 
  launch(exec, args, ctx); 
 
  ctx.stdout_behavior = inherit_stream(); 
  launch(exec, args, ctx); 
}

/*
The sample code above uses an inherited standard output stream. It starts a
small utility which is available on POSIX and Windows systems and writes the
hostname to the standard output stream. As the child process inherits the
standard output stream the hostname is written to the terminal window when
the program is run. There are no further steps required to make the output
of the child process visible.

By the way, the sample code above also shows that boost::process::find_executable_in_path() 
can find a program on Windows even if no file extension is given. It's not 
required to pass "hostname.exe" to boost::process::find_executable_in_path().

A more interesting and also more complex behavior is a captured stream. If for
example the standard input stream of a new process is captured the current
process can write data which will be received by the child process through
its standard input stream. The question how the current process accesses
and uses the captured stream is answered in the next section.
*/