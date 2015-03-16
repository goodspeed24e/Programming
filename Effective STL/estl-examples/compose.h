// The following is an excerpt from the SGI header stl_function.h.  It
// defines the function adapters compose1 and compose2 inside namespace
// std.

#include <functional>

#  define __UNARY_ARG(__Operation,__type)  __Operation::__type
#  define __BINARY_ARG(__Operation,__type) __Operation::__type
#  define __PAIR_ARG(__Pair,__type) __Pair::__type

namespace std {
  
  template <class _Operation1, class _Operation2>
  class unary_compose : 
    public unary_function<typename __UNARY_ARG(_Operation2,argument_type),
                          typename __UNARY_ARG(_Operation1,result_type)> {
  protected:
    _Operation1 _M_fn1;
    _Operation2 _M_fn2;
  public:
    unary_compose(const _Operation1& __x, const _Operation2& __y) 
      : _M_fn1(__x), _M_fn2(__y) {}
    typename _Operation1::result_type
    operator()(const typename _Operation2::argument_type& __x) const {
      return _M_fn1(_M_fn2(__x));
    }
  };
  
  template <class _Operation1, class _Operation2>
  inline unary_compose<_Operation1,_Operation2> 
  compose1(const _Operation1& __fn1, const _Operation2& __fn2)
  {
    return unary_compose<_Operation1,_Operation2>(__fn1, __fn2);
  }
  
  template <class _Operation1, class _Operation2, class _Operation3>
  class binary_compose : 
      public unary_function<typename __UNARY_ARG(_Operation2,argument_type),
                            typename __BINARY_ARG(_Operation1,result_type)> {
  protected:
    _Operation1 _M_fn1;
    _Operation2 _M_fn2;
    _Operation3 _M_fn3;
  public:
    binary_compose(const _Operation1& __x, const _Operation2& __y, 
                   const _Operation3& __z) 
      : _M_fn1(__x), _M_fn2(__y), _M_fn3(__z) { }
    typename _Operation1::result_type
    operator()(const typename _Operation2::argument_type& __x) const {
      return _M_fn1(_M_fn2(__x), _M_fn3(__x));
    }
  };
  
  template <class _Operation1, class _Operation2, class _Operation3>
  inline binary_compose<_Operation1, _Operation2, _Operation3> 
  compose2(const _Operation1& __fn1, const _Operation2& __fn2, 
           const _Operation3& __fn3)
  {
    return binary_compose<_Operation1,_Operation2,_Operation3>
      (__fn1, __fn2, __fn3);
  }

}
