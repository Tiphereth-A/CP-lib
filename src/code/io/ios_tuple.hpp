#ifndef TIFALIBS_IO_IOS_TUPLE
#define TIFALIBS_IO_IOS_TUPLE

#include "../util/util.hpp"

template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  return std::apply([&](Ts &...ts) { ((is >> ts), ...); }, p), is;
}
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> CR p) {
  return std::apply([&, n = 0](Ts const &...ts) mutable { ((os << ts << (++n != sizeof...(Ts) ? " " : "")), ...); }, p), os;
}

#endif