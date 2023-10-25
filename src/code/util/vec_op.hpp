#ifndef TIFA_LIBS_UTIL_VEC_OP
#define TIFA_LIBS_UTIL_VEC_OP

#include "util.hpp"

#define OO_PTEQ_(op)                                             \
  template <class T>                                             \
  constexpr vec<T> &operator op##=(vec<T> &a, vec<T> const &b) { \
    if (a.size() < b.size()) a.resize(b.size());                 \
    for (usz i = 0; i < b.size(); ++i) a[i] op## = b[i];         \
    return a;                                                    \
  }                                                              \
  template <class T>                                             \
  constexpr vec<T> operator op(vec<T> a, vec<T> const &b) { return a op## = b; }

OO_PTEQ_(+)
OO_PTEQ_(-)
OO_PTEQ_(*)
OO_PTEQ_(/)
OO_PTEQ_(%)
OO_PTEQ_(&)
OO_PTEQ_(|)
OO_PTEQ_(^)
OO_PTEQ_(<<)
OO_PTEQ_(>>)

#undef OO_PTEQ_

#endif