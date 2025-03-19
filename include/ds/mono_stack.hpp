#ifndef TIFALIBS_DS_MONO_STACK
#define TIFALIBS_DS_MONO_STACK

#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

template <class T, class Comp = std::less<T>>
class mono_stack {
  static CEXP Comp compare{};

  vec<T> s;

 public:
  CEXPE mono_stack() NE = default;

  CEXP void pop_greater(cT_(T) x) NE {
    while (!s.empty() && compare(x, s.back())) s.pop_back();
  }
  CEXP void push_nocheck(cT_(T) x) NE { s.push_back(x); }
  CEXP void push(cT_(T) x) NE { pop_greater(x), s.push_back(x); }
  CEXP T CR top() CNE { return s.back(); }
  CEXP u32 size() CNE { return (u32)s.size(); }
};

}  // namespace tifa_libs::ds

#endif