#ifndef TIFA_LIBS_UTIL_PAIR_OP
#define TIFA_LIBS_UTIL_PAIR_OP

#include "util.hpp"

namespace tifa_libs {

#define OO_PTEQ_(op)                                                                                                                                        \
  template <class T, class U>                                                                                                                               \
  constexpr auto operator op(std::pair<T, U> lhs, std::pair<T, U> const &rhs) { return std::pair<T, U>{lhs.first op rhs.first, lhs.second op rhs.second}; } \
  template <class T, class U>                                                                                                                               \
  constexpr std::pair<T, U> &operator op##=(std::pair<T, U> &lhs, std::pair<T, U> const &rhs) {                                                             \
    lhs.first op## = rhs.first;                                                                                                                             \
    lhs.second op## = rhs.second;                                                                                                                           \
    return lhs;                                                                                                                                             \
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