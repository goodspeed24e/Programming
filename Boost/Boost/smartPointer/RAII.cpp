/*
	The principle of smart pointers is based on a common idiom 
	named RAII: Resource acquisition is initialization. 

	Smart pointers are only one example for this idiom - certainly 
	a very prominent one. Smart pointers are used to ensure that 
	dynamically allocated memory is released properly under all 
	circumstances, freeing the developer from the burden of managing 
	this on her own. This includes scenarios in which execution of a 
	function is interrupted by an exception and the instruction to 
	release the memory is skipped. This guarantee is accomplished by
	initializing a smart pointer with the address of a dynamically allocated 
	object which in turn is used to release the memory during destruction. 
	Since the destructor is always executed the contained memory is therefore
	always released.

	RAII is applied whenever a second instruction is mandatory in order to
	release a resource previously allocated by another instruction. 

	Since many C++ applications require dynamically managed memory, smart 
	pointers are an important RAII class. RAII itself can be applied in many 
	other scenarios though.

	The above example defines a class named windows_handle that calls
	the function CloseHandle() in its destructor. Since it is a Windows 
	API function, the program can only be executed on Windows. 
	In Windows, many resources are required to be opened prior to their usage.
	This implicitly implies that resources should be closed once no longer used.
	The class windows_handle provides a mechanism to ensure just that.

	An instance of type windows_handle is initialized with a handle. Windows 
	utilizes handles in order to uniquely identify its resources. For example, 
	the function OpenProcess() returns a handle of type HANDLE that can be used
	to access a currently running process. In the code example, the own process
	is accessed - in other words the application itself.

	Using the returned handle, the process priority is increased allowing 
	the application to request more CPU time from the scheduler. This is 
	only for illustration purposes and does not serve any real benefit though.
	The important point here is that the resource opened with OpenProcess() 
	does not need to be explicitly closed using CloseHandle(). Certainly, 
	the resource is likely to be closed once the application terminates. 
	However, in more complex applications the class windows_handle ensures 
	that a resource is correctly closed if no longer needed.
	Once a particular resource leaves its visibility scope - in the above 
	example of h at the end of the function main() - the destructor 
	is automatically invoked which in turn closes the contained resource.
*/

#include <windows.h> 

class windows_handle 
{ 
  public: 
    windows_handle(HANDLE h) 
      : handle_(h) 
    { 
    } 

    ~windows_handle() 
    { 
      CloseHandle(handle_); 
    } 

    HANDLE handle() const 
    { 
      return handle_; 
    } 

  private: 
    HANDLE handle_; 
}; 

int main() 
{ 
  windows_handle h(OpenProcess(PROCESS_SET_INFORMATION, FALSE, GetCurrentProcessId())); 
  SetPriorityClass(h.handle(), HIGH_PRIORITY_CLASS); 
} 
