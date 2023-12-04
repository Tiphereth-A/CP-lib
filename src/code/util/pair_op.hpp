#ifndef TIFALIBS_UTIL_PAIR_OP
#define TIFALIBS_UTIL_PAIR_OP

#include "util.hpp"

#define OO_PTEQ_(op)                                                                                                                            \
  template <class T, class U>                                                                                                                   \
  constexpr auto operator op(std::pair<T, U> l, std::pair<T, U> const &r) { return std::pair<T, U>{l.first op r.first, l.second op r.second}; } \
  template <class T, class U>                                                                                                                   \
  constexpr std::pair<T, U> &operator op##=(std::pair<T, U> &l, std::pair<T, U> const &r) {                                                     \
    l.first op## = r.first;                                                                                                                     \
    l.second op## = r.second;                                                                                                                   \
    return l;                                                                                                                                   \
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

#endif