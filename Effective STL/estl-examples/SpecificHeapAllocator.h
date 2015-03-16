#if defined(_MSC_VER) && !defined(__MWERKS__) && !defined(__ICL) && !defined(__COMO__) && !defined(__BORLANDC__)
#define MSVC
# endif

#include <string>
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <list>

namespace MyLib {
  template<typename T, typename Heap>
  class SpecificHeapAllocator {
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
      typedef SpecificHeapAllocator<U, Heap> other;
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
    SpecificHeapAllocator() throw() {
      myMagicValue = -999;
    }
   
    explicit SpecificHeapAllocator(int x) {
      myMagicValue = x;
    }

    SpecificHeapAllocator(const SpecificHeapAllocator& rhs) throw() {
      myMagicValue = rhs.myMagicValue;
    }
#ifndef MSVC
    template <class U, typename Heap>
    SpecificHeapAllocator (const SpecificHeapAllocator<U, Heap>& rhs) throw() {
      myMagicValue = rhs.myMagicValue;
    }
#endif
    ~SpecificHeapAllocator() throw() {
    }

    // return maximum number of elements that can be allocated
    size_type max_size () const throw() {
#if defined (MSVC)
      return std::numeric_limits<size_t>::max() / sizeof(T);
#else
      return std::numeric_limits<std::size_t>::max() / sizeof(T);
#endif
    }

	pointer allocate(size_type numObjects, const void *localityHint = 0)
	{
		return static_cast<pointer>
			(Heap::alloc(numObjects * sizeof(T), localityHint));
	}

	void deallocate(pointer ptrToMemory, size_type numObjects)
	{
		Heap::dealloc(ptrToMemory);
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

    int myMagicValue;
  };

  // return that all specializations of this allocator are interchangeable
  template <class T1, class T2, typename Heap>
  bool operator== (const SpecificHeapAllocator<T1,Heap>&,
                   const SpecificHeapAllocator<T2, Heap>&) throw() {
    return true;
  }
  template <class T1, class T2, typename Heap>
  bool operator!= (const SpecificHeapAllocator<T1,Heap>&,
                   const SpecificHeapAllocator<T2, Heap>&) throw() {
    return false;
  }
}


#if defined(__SGI_STL_PORT) && defined(MSVC)
// Workaround for insufficient MSVC support for member templates;
// necessary to make the above allocator work with STLPort and MSVC
namespace std {

  template <class _Tp1, class _Tp2, typename Heap>
  inline MyLib::SpecificHeapAllocator<_Tp2, Heap>& __STL_CALL
  __stl_alloc_rebind(MyLib::SpecificHeapAllocator<_Tp1, Heap>& __a, const _Tp2*) 
  { return (MyLib::SpecificHeapAllocator<_Tp2, Heap>&)(__a); }

  template <class _Tp1, class _Tp2, typename Heap>
  inline MyLib::SpecificHeapAllocator<_Tp2, Heap> __STL_CALL
  __stl_alloc_create(const MyLib::SpecificHeapAllocator<_Tp1, Heap>&, const _Tp2*)
  { return MyLib::SpecificHeapAllocator<_Tp2, Heap>(); }

}
#endif

/*
int main()
{
  using namespace std;
  using namespace MyLib;

  SpecificHeapAllocator<int> allocator(44);
  list<int, SpecificHeapAllocator<int> > L(allocator);
  L.resize(1);
  return 0;
}
*/
