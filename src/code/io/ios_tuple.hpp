#ifndef TIFALIBS_IO_IOS_TUPLE
#define TIFALIBS_IO_IOS_TUPLE

#include "../util/util.hpp"

template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) NE {
  std::apply([&](Ts &...ts) NE { ((is >> ts), ...); }, p);
  return is;
}
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> CR p) NE {
  std::apply([&, n = 0](Ts const &...ts) mutable NE { ((os << ts << (++n != sizeof...(Ts) ? " " : "")), ...); }, p);
  return os;
}

#endif