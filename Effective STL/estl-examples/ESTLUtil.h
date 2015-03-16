// ---------------------------------------------------------------------------
// Utilities for use with Scott Meyers' "Effective STL" Course.
// Copyright 2000 by Scott Meyers.  
//
// Last modified 1/03/01.
//
// This file offers four basic utilities:
//   - A preprocessor symbol, MSVC, that's defined only when compiling with
//     MSVC. 
//   - Functions to help fill containers with seqences of values.  Search
//     for "makeSequence".
//   - Functions to print the contents of STL containers.  Search for 
//     "printContainer"
//   - A class to time how long it takes to do something.  Search for 
//     "Timer".  
// Note that everything in this file except MSVC is in the namespace
// ESTLUtils.  (Macros and preprocessor symbols never respect namespace
// boundaries.) 
//
// Platforms on which this header has so far been tested:
//   Borland C++ 5.5, native library, WinNT 4.0
//   MetroWerks CodeWarrior Pro 5.3, native library, WinNT 4.0 or
//     MetroWerks CodeWarrior Pro 6.0, native library, Windows 2000
//   Microsoft Visual C++ 6.0 (SP3), native library, WinNT 4.0
//   Gnu gcc 2.95.2 (mingw32 distribution), native library, WinNT 4.0
// ---------------------------------------------------------------------------
#ifndef ESTLUTILS_H
#define ESTLUTILS_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <ctime>


// ---------------------------------------------------------------------------
// MSVC, when used in conjunction with the library that ships with the
// compiler, has some limitations not present in most other compilers
// (e.g., it lacks member templates), so it's convenient to know when we're
// compiling with MSVC.  The following figures that out.  (In theory, all
// we need to do is look for the preprocessor symbol "_MSC_VER"), but other
// compilers for Windows define that, too, so we need to rule the other
// compilers out before concluding that we've got MSVC.)
//
// If you're using MSVC, but you're not using the library that ships with
// the compiler, much of the conditional compilation for MSVC may become
// unnecessary.  MSVC does have limitations, but it is a much more capable
// compiler than the library shipping with it suggests.
// ---------------------------------------------------------------------------
#if defined(_MSC_VER) && !defined(__MWERKS__) && !defined(__ICL) && !defined(__COMO__) && !defined(__BORLANDC__)
  #define MSVC
# endif


namespace ESTLUtils {

  // -------------------------------------------------------------------------
  // SequenceGenerator is a functor class template whose function objects
  // generate arithmetic sequences of values.  Rather than creating
  // SequenceGenerator objects directly, clients are expected to use the
  // convenience function makeSequence (see below).  (This is analogous to
  // how STL clients use make_pair() instead of creating pair<T1, T2>
  // objects directly.)
  //   
  // On the off chance you care, SequenceGenerator/makeSequence is a
  // generalization of the "iota" algorithm that was in the original STL
  // but that failed to make it into standard C++.
  // -------------------------------------------------------------------------
  template<typename T>
  class SequenceGenerator {
  public:
    SequenceGenerator(const T& initValue = T(), const T& increment = 1)
    : nextVal(initValue), incr(increment) {}

    T operator()()
    { 
      T valToReturn(nextVal);
      nextVal += incr;
      return valToReturn;
    }

  private:
    T nextVal;
    T incr;
  };

  // -------------------------------------------------------------------------
  // The makeSequence functions generate objects that themselves generate
  // sequences of values.  By default, the values are of type int, the
  // initial value is 0, and the increment between values is 1.  All these
  // defaults may be overridden.  makeSequence is designed to be used with
  // the generate_n algorithm to fill containers with values.  Here are
  // three examples of how it is expected to be used:
  //
  //   list<int> L;
  //   generate_n(back_inserter(L), 5,     // insert 0, 1, 2, 3, 4, and 5
  //              makeSequence());         // into L
  //
  //   vector<int> v;
  //   generate_n(back_inserter(v), 3,     // insert 50, 51, and 52 into v
  //              makeSequence(50));
  //
  //   deque<double> d;
  //   generate_n(back_inserter(d), 10,    // insert 0.5, 1.5, ..., 9.5
  //              makeSequence(0.5, 1.0)); // into d
  //
  // Note that makeSequence() can't be used to generate values for maps or
  // multimaps, because it generates sequences of individual values, not
  // sequences of pairs.
  // -------------------------------------------------------------------------
  SequenceGenerator<int> makeSequence()
  { 
    return SequenceGenerator<int>(0, 1);
  }

  template<typename T>
  SequenceGenerator<T> makeSequence(const T& initValue = T(),
                                    const T& increment = 1)
  {
    return SequenceGenerator<T>(initValue, increment);
  }

  
  // -------------------------------------------------------------------------
  // The following templates generate functions to print the contents of
  // one or two containers:
  //    
  //   show(container);				// LZ's super-lazy version of printContainer(name, container)
  //   show2(container,container);	// LZ's super-lazy version of printContainer(name1, c1, name2, c2)
  //   printContainer(container);
  //   printContainer(container, stream);
  //   printContainer(name, container);
  //   printContainer(name, container, stream);
  //
  //   printContainers(container1, container2);
  //   printContainers(container1, container2, stream);
  //   printContainers(name1, container1, name2, container2);
  //   printContainers(name1, container1, name2, container2, stream);
  //
  // For containers of pointers other than char* and const char*, each of
  // the above dereferences each pointer before printing.  Containers of
  // pairs (including maps and multimaps) print each pair like this:
  // "(key,value)".
  //
  // For most platforms, the implementation is relatively straightforward:
  // printContainers creates and invokes printValue objects, and printValue
  // is partially specialized for pairs and pointer types and fully
  // specialized for char* and const char* types.  Alas, MSVC lacks support
  // for partial specialization, so we have to play games from the world of
  // template metaprogramming, and even those we have to modify to work
  // around the lack of partial specialization.  The MSVC implementation is
  // based on a posting to comp.lang.c++.moderated by Aleksey Gurtovoy.
  // -------------------------------------------------------------------------

#define show(container) printContainer(#container, container);
#define show2(c1, c2) printContainers(#c1, c2, #c2, c2);

#ifndef MSVC
  // Print a non-pointer value.  (A specialization for when T=std::pair is
  // below.)
  template<typename T>
  struct printValue {
    void operator()(std::ostream& s, const T& val) const
    { s << val; }
  };

  // Print a pointed-to value.  (Specializations for char* and const char*
  // are below.)
  template<typename T>
  struct printValue<T*> {
    void operator()(std::ostream& s, const T* pVal) const 
    { s << *pVal; } 
  };

  // print a const char*
  template<>
  struct printValue<const char*> {
    void operator()(std::ostream& s, const char* pVal) const 
    { s << pVal; } 
  };

  // print a char*
  template<>
  struct printValue<char*> {
    void operator()(std::ostream& s, char* pVal) const 
    { s << pVal; } 
  };

  // print a std::pair
  template<typename K, typename V>
  struct printValue<std::pair<K, V> > {
    void operator()(std::ostream& s, const std::pair<K, V>& p) const
    { 
      s << '(';
      printValue<K>()(s, p.first);
      s << ',';
      printValue<V>()(s, p.second);
      s << ')';
    }
  };
#else
  // MSVC lacks partial template specialization, so the approach above
  // won't work.  Instead, we call TypeQuery::examine on an object of type
  // T, and the result type of the function call is used as an additional
  // argument to drive overloading resolution among several functions named
  // printValue.
  struct IsAPtr {};             // TypeQuery::examine returns this if T is
                                // a pointer.
  struct IsAPair {};            // It returns this if T is a std::pair.
  struct IsNothingSpecial {};   // Otherwise it returns this type.

  struct TypeQuery {
    static IsAPtr examine(const void*) { return IsAPtr(); }

    template<typename K, typename V>
    static IsAPair examine(const std::pair<K, V>&) { return IsAPair(); }

    static IsNothingSpecial examine(...) { return IsNothingSpecial(); }
  };

  // Print a non-pointer value.  (A specialization for when T=std::pair is
  // below.)
  template<typename T>
  void printValue(std::ostream& s, const T& val, IsNothingSpecial)
  { s << val; }
  
  // Print a pointed-to value.  (Specializations for char* and const char*
  // are below.)
  template<typename T>
  void printValue(std::ostream& s, const T& val, IsAPtr)
  { s << *val; }

  // print a const char*
  template<>
  void printValue<const char*>(std::ostream& s, const char * const & val,
                               IsAPtr) 
  { s << val; }

  // print a char*
  template<>
  void printValue<char*>(std::ostream& s, char * const & val, IsAPtr)
  { s << val; }

  // print a std::pair
  template<typename K, typename V>
  void printValue(std::ostream& s, const std::pair<K, V>& p,
                  IsAPair)
    { 
      s << '(';
      printValue(s, p.first, TypeQuery::examine(p.first));
      s << ',';
      printValue(s, p.second, TypeQuery::examine(p.second));
      s << ')';
    }
#endif

  ////////////////////////////////////////////////////////////////////////////
  // In case you're looking for it, here's the main printContainer function.
  ////////////////////////////////////////////////////////////////////////////
  template<typename Container>
  void printContainer(const Container& c, std::ostream& s = std::cout)
  {
    using namespace std;

    // for non-MSVC, we could probably use for_each and bind1st to
    // eliminate the explicit loop, but this works fine, and it's easier to
    // understand for new STL users.
    for (typename Container::const_iterator b = c.begin();
         b != c.end();
         ++b) {
#ifndef MSVC
      printValue<typename Container::value_type>()(s, *b);
#else
      printValue(s, *b, TypeQuery::examine(*b));
#endif
      s << ' ';
    }
    s << endl;
  }

#ifndef MSVC
  // This version of printContainer is for when the container is a string.
  // It prints the contents of the string as you'd expect.
  void printContainer(const std::string& s, std::ostream& stream = std::cout)
  { 
    using namespace std;

    stream << s << endl; 
  }
#else
  // MSVC thinks the above function is a specialization of
  // printContainer<Container> instead of a standalone function.  To
  // suppress that interpretation, we give this version of printContainer
  // an extra, unused, parameter with a default value (so callers can
  // ignore it).  Thanks to Eric Merrill for the workaround.
  void printContainer(const std::string& s, std::ostream& stream = std::cout,
                      int /* dummyParameter */ = 0)
  { 
    using namespace std;

    stream << s << endl; 
  }
#endif

  template<typename Container>
  void printContainer(const char *name, const Container& c,
                      std::ostream& s = std::cout)
  {
    using namespace std;

    cout << name << ": ";
    printContainer(c, s);
  }

  template<typename Container>
  void printContainer(const std::string& name, const Container& c,
                      std::ostream& s = std::cout)
  {
    printContainer(name.c_str(), c, s);
  }

  template<typename Container1, typename Container2>
  void printContainers(const Container1& c1, const Container2& c2,
                       std::ostream& s = std::cout)
  {
    printContainer(c1, s);
    printContainer(c2, s);
  }

  template<typename Container1, typename Container2>
  void printContainers(const char *name1, const Container1& c1,
                       const char *name2, const Container2& c2,
                       std::ostream& s = std::cout)
  {
    printContainer(name1, c1, s);
    printContainer(name2, c2, s);
  }

  template<typename Container1, typename Container2>
  void printContainers(const std::string& name1, const Container1& c1,
                       const std::string& name2, const Container2& c2,
                       std::ostream& s = std::cout)
  {
    printContainers(name1.c_str(), c1, name2.c_str(), c2, s);
  }


  // -------------------------------------------------------------------------
  // A Timer object keeps track of CPU time used since the object was
  // created or last reset.  It implicitly converts to a double, so it can
  // be used like this:
  //
  //   Timer t;             // begin timing some operation
  //   ...
  //   cout << t;           // print out how much CPU time has elapsed
  //                        // in seconds
  //
  // MSVC doesn't understand that the contents of <ctime> are supposed to
  // be in std, so for MSVC, we make them global.  Note that the macro
  // CLOCKS_PER_SEC is global regardless.  After all, it's a macro.
  // ---------------------------------------------------------------------------
#ifdef MSVC
  #define STD_CLOCK_T  clock_t
  #define STD_CLOCK    clock
  #define STD_DIFFTIME difftime  
#else
  #define STD_CLOCK_T  std::clock_t
  #define STD_CLOCK    std::clock
  #define STD_DIFFTIME std::difftime  
#endif 
  
  class Timer {
  public:
    Timer(): start(STD_CLOCK()) {}
    
    operator double() const 
    { return STD_DIFFTIME(STD_CLOCK(), start) / CLOCKS_PER_SEC; }
    
    void reset() { start = STD_CLOCK(); }
    
  private:
    STD_CLOCK_T start;
  };

}  // namespace ESTLUtils

#endif


