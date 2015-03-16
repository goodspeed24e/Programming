/*
After meeting the different smart pointers of the Boost C++ Libraries, one
should be able to write safe code for dynamically allocated objects as well
as arrays. Many times, these objects are required to be stored within a 
container which - as seen above - is fairly easy using boost::shared_ptr 
and boost::shared_array.
*/
//#include <boost/shared_ptr.hpp> 
//#include <vector> 
//
//int main() 
//{ 
//  std::vector<boost::shared_ptr<int> > v; 
//  v.push_back(boost::shared_ptr<int>(new int(1))); 
//  v.push_back(boost::shared_ptr<int>(new int(2))); 
//}

/*
While the code in the above example is absolutely correct and smart pointers
can be used the given way, it is actually impractical for a couple of 
reasons. For once, the repetitive declaration of boost::shared_ptr requires 
more typing. In addition, copying the boost::shared_ptr to, from or within
the container requires incrementing and decrementing the internal
reference count constantly and thus is deemed very inefficient. 
For these reasons, the Boost C++ Libraries provide Pointer Container that
are specialized for the management of dynamically allocated objects.
*/
#include <boost/ptr_container/ptr_vector.hpp> 

int main() 
{ 
  boost::ptr_vector<int> v; 
  v.push_back(new int(1)); 
  v.push_back(new int(2)); 

  std::cout << v[0] << "---" << v[1] << std::endl;
}
/*
The class boost::ptr_vector defined in boost/ptr_container/ptr_vector.hpp 
works the same way as the container used and initialized with the 
boost::shared_ptr template parameter in the previous example.

Since boost::ptr_vector is specialized for dynamically allocated objects, it
is easier and more efficient to use though. However, as boost::ptr_vector
is the solely owner of all contained objects, the ownership cannot be shared
with a shared pointer not stored inside the container opposed to using
std::vector<boost::shared_ptr<int> >.

Besides boost::ptr_vector, additional containers specialized for managing
dynamically allocated objects are available including 
boost::ptr_deque, 
boost::ptr_list, 
boost::ptr_set,
boost::ptr_map,
boost::ptr_unordered_set
and boost::ptr_unordered_map.
These containers are equivalent to the ones provided by the C++ standard.
The last two containers match the std::unordered_set and std::unordered_map
containers added to the C++ standard as part of the Technical Report 1. 
They are also implemented as boost::unordered_set and boost::unordered_map 
by the Boost C++ Libraries that can be utilized if the used implementation
of the C++ Standard does not support the Technical Report 1.
*/
