#ifndef TIFALIBS_IO_IOS_TUPLE
#define TIFALIBS_IO_IOS_TUPLE

#include "../util/util.hpp"

template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  return std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p), is;
}
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> CR p) {
  std::apply(
      [&](Ts CR... targs) {
        usz n = 0;
        ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
      },
      p);
  return os;
}

#endif