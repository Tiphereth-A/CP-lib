#ifndef TIFALIBS_DS_MONO_STACK
#define TIFALIBS_DS_MONO_STACK

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, class Comp = std::less<T>>
class mono_stack {
  static CEXP Comp compare{};

  vec<T> s;
  template <bool use_bf = false>
  CEXP auto find_(cT_(T) x) NE {
    if CEXP (use_bf) {
      auto it = s.rbegin();
      while (it != s.rend() && compare(x, *it)) ++it;
      return (--it).base();
    } else return upper_bound(s, x, compare);
  }

 public:
  CEXPE mono_stack() NE = default;

  template <bool use_bf = false>
  CEXP void pop_greater(cT_(T) x) NE { s.erase(find_<use_bf>(x), s.end()); }
  CEXP void push_nocheck(cT_(T) x) NE { s.push_back(x); }
  template <bool use_bf = false>
  CEXP void push(cT_(T) x) NE { pop_greater<use_bf>(x), s.push_back(x); }
  template <bool use_bf = false>
  CEXP void insert(cT_(T) x) NE {
    if (auto it = find_<use_bf>(x); it == s.end()) s.push_back(x);
    else *it = x;
  }
  CEXP T CR top() CNE { return s.back(); }
  CEXP u32 size() CNE { return (u32)s.size(); }
};

}  // namespace tifa_libs::ds

#endif