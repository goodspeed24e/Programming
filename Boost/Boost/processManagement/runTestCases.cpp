/*
  Making sure Boost.Process works on your platform
*/

/*
Boost.Process ships numerous test cases which can be run to verify that the library works 
correctly on a platform. The test cases can be found in the directory libs/process/test.

As Boost.Process is a library to manage processes nearly all test cases create at least one
child process. All test cases access a helper program to do so. For this to work test cases must
know where to find this helper program. The problem is though that when test cases are run 
compilers create different directories to build the test cases. As directory names are 
different depending on the compiler used it's difficult for test cases to find the helper 
program.

Currenly the path of the helper program is hardcoded in libs/process/test/misc.hpp. Before you 
run the test cases you must check the hardcoded path in libs/process/test/misc.hpp and 
eventually update it. If you don't do you might see lots of failures when you run the test 
cases as they simply might not be able to find the helper program.

When you have verified that the path to the helper program is set correctly you can run the 
test cases. Change to the directory libs/process/test and run bjam. You don't need to pass any
command line arguments. The helper program and all test cases will be automatically built and 
run.

Boost.Process 0.3x has been tested successfully with the following compilers and platforms so
far:

Visual C++ 2008, Windows XP SP 3

Visual C++ 2008, Windows Vista SP 1

GCC 3.4.4, Cygwin

GCC 3.4.6, Solaris 10 (SPARC)

Sun C++ 5.9, Solaris 10 (SPARC)

GCC 4.1.2, Linux 32-bit

GCC 4.2.1, Linux 32-bit

On POSIX systems (except Cygwin) Boost.Test must be patched though. There is a problem with the
way Boost.Test treats the SIGCHLD signal. A macro has been proposed but hasn't been added yet
to Boost.Test. For the test cases of Boost.Process to work one line in a Boost.Test file has
to be changed manually. What has to be done exactly has been explained in a message to the 
Boost mailing list. There are also a few more explanations about how to run the test cases on
the various platforms. Although the message is from September 2008 the explanations are still 
up-to-date.
*/