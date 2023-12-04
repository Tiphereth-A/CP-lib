#ifndef TIFALIBS_UTIL_IOS_TUPLE
#define TIFALIBS_UTIL_IOS_TUPLE

#include "util.hpp"

template <typename... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p);
  return is;
}
template <typename... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &p) {
  std::apply(
      [&](Ts const &...targs) {
        usz n = 0;
        ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
      },
      p);
  return os;
}

#endif