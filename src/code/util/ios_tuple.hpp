#ifndef TIFA_LIBS_UTIL_IOS_TUPLE
#define TIFA_LIBS_UTIL_IOS_TUPLE

#include "util.hpp"

template <typename... Ts>
inline std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p);
  return is;
}
template <typename... Ts>
inline std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &p) {
  std::apply(
      [&](Ts const &...targs) {
        std::size_t n{0};
        ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
      },
      p);
  return os;
}

#endif