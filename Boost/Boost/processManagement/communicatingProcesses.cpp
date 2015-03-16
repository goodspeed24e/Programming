/*
Exchanging data - even asynchronously
*/

/*
Boost.Process enables processes to communicate with each other only if they 
are related: One process must have created the other. If you want two 
processes which are not related to exchange data you should use 
Boost.Interprocess.
*/

/*
The functions boost::process::launch() and boost::process::launch_shell() 
which are used to spawn a child process return an object of type 
boost::process::child. This class is derived from boost::process::process. 
It defines three methods get_stdin(), get_stdout() and get_stderr(). While 
get_stdin() returns an object of type boost::process::postream the methods get_stdout() and get_stderr() return an object of type boost::process::pistream.

These objects of type boost::process::postream and 
boost::process::pistream represent standard input and standard output 
streams of another process. It is important to understand that 
boost::process::postream is an input stream and boost::process::pistream 
an output stream of another process. That's why get_stdin() returns an 
object of type boost::process::postream. From the view of the current 
process the standard input stream of the other process is an output stream 
though. The current process has to write data to an output stream which is 
then received through the standard input stream by the other process.

It should also be noted that objects of type boost::process::postream and 
boost::process::pistream can only be used if the stream behaviors have been 
set correctly: Streams must be captured with boost::process::capture_stream().
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
//  ctx.stdout_behavior = capture_stream(); 
//  child c = launch(exec, args, ctx); 
//  pistream &is = c.get_stdout(); 
//  std::cout << is.rdbuf(); 
//}

/*
The classes boost::process::postream and boost::process::pistream behave 
like other streams from the C++ standard. In fact boost::process::postream 
is derived from std::ostream and boost::process::pistream from std::istream.

The only additional methods defined by boost::process::postream and 
boost::process::pistream are handle() and close(). While close() obviously 
closes the stream handle() returns an object of type boost::process::detail::file_handle.

boost::process::detail::file_handle implements another concept of 
Boost.Process called handle. It hasn't been introduced yet in this article
as it's not clear if this concept is really useful. As you can see this 
class is defined within the detail namespace of boost::process. Classes 
defined in this namespace are not really meant to be used by other developers.

The method handle() was added in Boost.Process 0.3. It is the only way to 
get the underlying native handle of a stream. On POSIX systems this handle
is called file descriptor while on Windows systems it's also called handle.
Getting the native handle is required for asynchronous operations.
*/

/*
Boost.Asio is the Boost C++ library to support asynchronous input/output 
operations. It defines I/O objects which represent devices to write and 
read data asynchronously. There is for example a socket I/O object to 
transmit data over a network. There is also a generic I/O object which can
be initialized with a handle. As Boost.Process provides the method handle()
to get a handle we can use the generic I/O object of Boost.Asio for 
asynchronous read and write operations.
*/

#include <boost/asio.hpp> 
#define BOOST_PROCESS_WINDOWS_USE_NAMED_PIPE 
#include <boost/process.hpp> 
#include <boost/array.hpp> 
#include <boost/bind.hpp> 
#include <boost/assign/list_of.hpp> 
#include <string> 
#include <vector> 
#include <iostream> 

using namespace boost::process; 
using namespace boost::asio; 

io_service ioservice; 
boost::array<char, 4096> buf; 

#if defined(BOOST_POSIX_API) 
posix::stream_descriptor in(ioservice); 
#elif defined(BOOST_WINDOWS_API) 
windows::stream_handle in(ioservice); 
#endif 

void begin_read(); 
void end_read(const boost::system::error_code &ec, std::size_t bytes_transferred); 

int main() 
{ 
  std::string exec = find_executable_in_path("hostname"); 
  std::vector<std::string> args = boost::assign::list_of("hostname"); 
  context ctx; 
  ctx.environment = self::get_environment(); 
  ctx.stdout_behavior = capture_stream(); 
  child c = launch(exec, args, ctx); 
  pistream &is = c.get_stdout(); 
  in.assign(is.handle().release()); 
  begin_read(); 
  ioservice.run(); 
} 

void begin_read() 
{ 
  in.async_read_some(boost::asio::buffer(buf), 
    boost::bind(&end_read, placeholders::error, placeholders::bytes_transferred)); 
} 

void end_read(const boost::system::error_code &ec, std::size_t bytes_transferred) 
{ 
  if (!ec) 
  { 
    std::cout << std::string(buf.data(), bytes_transferred) << std::flush; 
    begin_read(); 
  } 
}

/*
If you look at the sample code above you'll probably agree that it should 
be easier to use asynchronous operations without passing native handles 
around. Getting the native file handle and initializing the generic I/O 
object of Boost.Asio doesn't seem to be a good solution. As there are in 
fact two different implementations of the generic I/O object - one for 
POSIX and one for Windows systems - it gets even worse due to preprocessor 
directives which have to be used.

Furthermore asynchronous operations only work on Windows if the macro 
BOOST_PROCESS_WINDOWS_USE_NAMED_PIPE is defined. By default, Boost.Process 
creates an anonymous pipe if a stream is captured. However anonymous pipes 
don't support asynchronous operations on Windows. On Windows a named pipe 
must be created for asynchronous operations to work.

Defining the macro BOOST_PROCESS_WINDOWS_USE_NAMED_PIPE makes Boost.Process 
create named pipes for all streams on Windows even if a developer wants to 
use asynchronous operations only for some streams. As named pipes can be 
useful in other scenarios it would be better if Boost.Process supported 
named pipes explicitly. The library should offer developers a choice 
between anonymous and named pipes. Of course named pipes wouldn't support 
asynchronous operations on Windows. But developers could use named pipes in 
other use cases if they were only supported explicitly. As named pipes are 
called FIFO on POSIX systems there could be two classes boost::process::pipe 
and boost::process::fifo defined. The Windows documentation doesn't refer
to named pipes as FIFO. But then again on POSIX systems a pipe is always 
anonymous - FIFO is used to name the other interprocess mechanism.
*/