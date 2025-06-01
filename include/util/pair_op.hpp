#ifndef TIFALIBS_UTIL_PAIR_OP
#define TIFALIBS_UTIL_PAIR_OP

#include "util.hpp"

namespace tifa_libs {

#define OO_PTEQ_(op)                                                                                                                      \
  template <class T, class U>                                                                                                             \
  CEXP auto operator op(std::pair<T, U> l, std::pair<T, U> CR r) NE { return std::pair<T, U>{l.first op r.first, l.second op r.second}; } \
  template <class T, class U>                                                                                                             \
  CEXP std::pair<T, U> &operator op##=(std::pair<T, U> &l, std::pair<T, U> CR r) NE {                                                     \
    l.first op## = r.first, l.second op## = r.second;                                                                                     \
    return l;                                                                                                                             \
  }

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

#endif