/*
In general, the intrusive pointer works exactly as the shared pointer. 
However, while boost::shared_ptr internally keeps track of the number of 
shared pointers referencing a particular object, the developer has to keep
track of this information for the intrusive pointer. 

This is particularly helpful for e.g. framework objects that already keep 
track of the number of times they are referenced themselves. 

The intrusive pointer is defined as boost::intrusive_ptr in
boost/intrusive_ptr.hpp.
*/
#include <boost/intrusive_ptr.hpp> 
#include <atlbase.h> 
#include <iostream> 

void intrusive_ptr_add_ref(IDispatch *p) 
{ 
  p->AddRef(); 
} 

void intrusive_ptr_release(IDispatch *p) 
{ 
  p->Release(); 
} 

void check_windows_folder() 
{ 
  void *p; 
  CLSID clsid; 
  CLSIDFromProgID(CComBSTR("Scripting.FileSystemObject"), &clsid); 

  CoCreateInstance(clsid, 0, CLSCTX_INPROC_SERVER, __uuidof(IDispatch), &p);
  boost::intrusive_ptr<IDispatch> disp(static_cast<IDispatch*>(p)); 
  CComDispatchDriver dd(disp.get()); 
  CComVariant arg("C:\\Windows"); 
  CComVariant ret(false); 
  dd.Invoke1(CComBSTR("FolderExists"), &arg, &ret); 
  std::cout << (ret.boolVal != 0) << std::endl; 
} 

void main() 
{ 
  CoInitialize(0); 
  check_windows_folder(); 
  CoUninitialize(); 
}
/*
The above example uses functions provided by COM (Component Object Model) 
thus, only builds and executes under the Windows platform. COM objects are
a perfect example for boost::intrusive_ptr since they keep track of the
number of pointers referencing them. The internal reference count can be
incremented or decremented by 1 using the AddRef() or Release() method 
respectively. Once the counter reaches 0, the COM object is automatically
destroyed.

The two methods AddRef() and Release() are called from within the
intrusive_ptr_add_ref() and intrusive_ptr_release() functions to 
increment and decrement the internal reference counter of the 
corresponding COM object. The COM object used in this example is named
'FileSystemObject' and is available in Windows by default. It allows
access to the underlying file system to e.g. verify whether or not a 
given directory exists. In the above example, the existence of a
directory named C:\Windows is checked. How that works internally depends
solely on COM and is irrelevant in regards to the functionality of 
boost::intrusive_ptr. The crucial point is that once the intrusive 
pointer disp loses its scope at the end of the check_windows_folder() 
function, the function intrusive_ptr_release() is going to be 
automatically called. This in turn will decrement the internal reference 
counter of the COM object 'FileSystemObject' to 0 and thus destroy the 
object.
*/
