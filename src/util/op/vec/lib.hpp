#pragma once

#include "../../alias/others/lib.hpp"

namespace tifa_libs {

#define OO_PTEQ_(op)                                          \
  template <class T>                                          \
  CEXP vec<T>& operator op## = (vec<T> & a, vec<T> CR b) NE { \
    if (a.size() < b.size()) a.resize(b.size());              \
    for (usz i = 0; i < b.size(); ++i) a[i] op## = b[i];      \
    return a;                                                 \
  }                                                           \
  template <class T>                                          \
  CEXP vec<T> operator op(vec<T> a, vec<T> CR b) NE { return a op## = b; }

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

}  // namespace tifa_libs
