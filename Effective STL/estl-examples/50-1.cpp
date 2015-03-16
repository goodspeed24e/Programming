//
// Example from ESTL Item 50
// (requires SGI library)
//

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include "ESTLUtil.h"
using namespace std;

// select1st and select2nd are extensions: they are not part of the standard.
template <class _Pair>
struct _Select1st : public unary_function<_Pair, typename _Pair::first_type> {
  const typename _Pair::first_type& operator()(const _Pair& __x) const {
    return __x.first;
  }
};

template <class _Pair>
struct _Select2nd : public unary_function<_Pair, typename _Pair::second_type>
{
  const typename _Pair::second_type& operator()(const _Pair& __x) const {
    return __x.second;
  }
};


template <class _Pair> struct select1st : public _Select1st<_Pair> {};
template <class _Pair> struct select2nd : public _Select2nd<_Pair> {};


int main()
{
        using namespace std;
        using namespace ESTLUtils;

		typedef  map<int, string> M;

        M m;

		m.insert(M::value_type(10, string("hello")));
		m.insert(M::value_type(20, string("goodbye")));
		m.insert(M::value_type(30, string("Tangerine Dream Rules!")));
		show(m);

        // write all the map keys to cout
        transform(m.begin(), m.end(),
                          ostream_iterator<int>(cout, "\n"),
                          select1st<map<int, string>::value_type>());

        // create a vector and copy all the values in the map into it
        vector<string> v;
        transform(m.begin(), m.end(), back_inserter(v),
                          select2nd<map<int, string>::value_type>());

		show(v);

        return 0;
}
