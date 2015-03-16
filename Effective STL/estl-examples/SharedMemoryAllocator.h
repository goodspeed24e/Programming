#if defined(_MSC_VER) && !defined(__MWERKS__) && !defined(__ICL) && !defined(__COMO__) && !defined(__BORLANDC__)
#define MSVC
# endif

#include <string>
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <list>

namespace MyLib {
  template <class T>
  class SharedMemoryAllocator {
  public:
    // type definitions
    typedef T        value_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
#ifndef MSVC
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;
#else
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;
#endif
    // rebind allocator to type U
    template <class U>
    struct rebind {
      typedef SharedMemoryAllocator<U> other;
    };

    // return address of values
    pointer address (reference value) const {
      return &value;
    }
    const_pointer address (const_reference value) const {
      return &value;
    }

    /* constructors and destructor
     * - nothing to do because the allocator has no state
     */
    SharedMemoryAllocator() throw() {
      myMagicValue = -999;
    }
   
    explicit SharedMemoryAllocator(int x) {
      myMagicValue = x;
    }

    SharedMemoryAllocator(const SharedMemoryAllocator& rhs) throw() {
      myMagicValue = rhs.myMagicValue;
    }
#ifndef MSVC
    template <class U>
    SharedMemoryAllocator (const SharedMemoryAllocator<U>& rhs) throw() {
      myMagicValue = rhs.myMagicValue;
    }
#endif
    ~SharedMemoryAllocator() throw() {
    }

    // return maximum number of elements that can be allocated
    size_type max_size () const throw() {
#if defined (MSVC)
      return std::numeric_limits<size_t>::max() / sizeof(T);
#else
      return std::numeric_limits<std::size_t>::max() / sizeof(T);
#endif
    }

    // allocate but don't initialize num elements of type T
	pointer allocate(size_type numObjects, const void *localityHint = 0)
	{
		return static_cast<pointer>(mallocShared(numObjects * sizeof(T)));
	}

    // initialize elements of allocated storage p with value value
    void construct (pointer p, const T& value) {
      // initialize memory with placement new
      new((void*)p)T(value);
    }

    // destroy elements of initialized storage p
    void destroy (pointer p) {
      // destroy objects by calling their destructor
      p->~T();
    }

    // deallocate storage p of deleted elements
	void deallocate(pointer ptrToMemory, size_type numObjects)
	{
		freeShared(ptrToMemory);
	}

    int myMagicValue;
  };

  // return that all specializations of this allocator are interchangeable
  template <class T1, class T2>
  bool operator== (const SharedMemoryAllocator<T1>&,
                   const SharedMemoryAllocator<T2>&) throw() {
    return true;
  }
  template <class T1, class T2>
  bool operator!= (const SharedMemoryAllocator<T1>&,
                   const SharedMemoryAllocator<T2>&) throw() {
    return false;
  }
}


#if defined(__SGI_STL_PORT) && defined(MSVC)
// Workaround for insufficient MSVC support for member templates;
// necessary to make the above allocator work with STLPort and MSVC
namespace std {

  template <class _Tp1, class _Tp2>
  inline MyLib::SharedMemoryAllocator<_Tp2>& __STL_CALL
  __stl_alloc_rebind(MyLib::SharedMemoryAllocator<_Tp1>& __a, const _Tp2*) 
  { return (MyLib::SharedMemoryAllocator<_Tp2>&)(__a); }

  template <class _Tp1, class _Tp2>
  inline MyLib::SharedMemoryAllocator<_Tp2> __STL_CALL
  __stl_alloc_create(const MyLib::SharedMemoryAllocator<_Tp1>&, const _Tp2*)
  { return MyLib::SharedMemoryAllocator<_Tp2>(); }

}
#endif

/*
int main()
{
  using namespace std;
  using namespace MyLib;

  SharedMemoryAllocator<int> allocator(44);
  list<int, SharedMemoryAllocator<int> > L(allocator);
  L.resize(1);
  return 0;
}
*/
