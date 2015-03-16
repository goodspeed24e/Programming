/*
Better support of Unix platforms
*/
/*
You have already been introduced to the class boost::process::posix_status.
In the beginning of this article another POSIX class has been mentioned 
though: boost::process::posix_child.

The class boost::process::posix_child supports features which are only 
available on POSIX systems. To create a POSIX child process you don't use 
boost::process::launch() but boost::process::posix_launch(). This function
has the same signature as boost::process::launch() but returns an object 
of type boost::process::posix_child. The context which is passed to 
boost::process::posix_launch() must be based on boost::process::posix_context
though.
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
//  std::string exec = find_executable_in_path("hostname"); 
//  std::vector<std::string> args = boost::assign::list_of("hostname"); 
//  posix_context ctx; 
//  ctx.environment = self::get_environment(); 
//  posix_child c = posix_launch(exec, args, ctx); 
//}

/*
If you lookup the reference of boost::process::posix_child you'll see that
there are only two additional methods get_input() and get_output() defined.
Both expect a file descriptor as an argument and return an input or output
stream corresponding to the file descriptor. The reason is that on POSIX 
systems a child process can have more input and output streams than the 
three standard ones. Of course they need to be setup first. Thus in the 
sample code above it doesn't make any sense to use boost::process::posix_launch()
because no additional streams have been setup.
*/

//#include <boost/process.hpp> 
//#include <boost/assign/list_of.hpp> 
//#include <string> 
//#include <vector> 
//#include <iostream> 
//#include <unistd.h> 
//#include <sys/types.h> 
//
//using namespace boost::process; 
//
//int main() 
//{ 
//  std::string exec = find_executable_in_path("dbus-daemon"); 
//  std::vector<std::string> args = boost::assign::list_of("dbus-daemon") 
//    ("--session")("--fork")("--print-address=3")("--print-pid=4"); 
//  posix_context ctx; 
//  ctx.output_behavior.insert(behavior_map::value_type(STDOUT_FILENO, inherit_stream())); 
//  ctx.output_behavior.insert(behavior_map::value_type(STDERR_FILENO, inherit_stream())); 
//  ctx.output_behavior.insert(behavior_map::value_type(3, capture_stream())); 
//  ctx.output_behavior.insert(behavior_map::value_type(4, capture_stream())); 
//  ctx.environment = self::get_environment(); 
//  posix_child c = posix_launch(exec, args, ctx); 
//  std::string address; 
//  pid_t pid; 
//  c.get_output(3) >> address; 
//  c.get_output(4) >> pid; 
//  std::cout << "Address: " << address << "\nPID: " << pid << std::endl; 
//}

/*
In the sample above a programm called dbus-daemon is used. What D-Bus is 
and what this program does it not important. The program is used because 
it supports command line arguments which make the program write data to 
certain streams. As the file descriptors of those streams can be specified
on the command line, too, dbus-daemon makes it easy to play with the 
boost::process::posix_child class.

First the context has to be configured: The streams based on the file 
descriptors 3 and 4 are captured as these are the streams dbus-daemon 
will write data to. The class boost::process::posix_context provides two 
public properties input_behavior and output_behavior. Both properties are 
based on a type behavior_map which is a typedef for std::map<int, stream_behavior>.

As POSIX systems support more streams than the three standard ones every 
stream represented by a file descriptor can be a behavior setting assigned.
In the code sample above the streams based on the file descriptors 3 and 4
are captured. The streams 1 and 2 - the sample uses STDOUT_FILENO and 
STDERR_FILENO from unistd.h - are inherited.

When the child process is created the respective streams are accessed by 
passing the file descriptors as sole arguments to get_output(). This method
returns an object of type boost::process::postream which works as usual.

Apart from the properties input_behavior and output_behavior the class 
boost::process::posix_context also provides uid, euid, gid, egid and 
chroot. Developers familiar with POSIX operating systems should understand
the purpose of those properties immediately.
*/