#ifndef TIFALIBS_IO_IOS_TUPLE
#define TIFALIBS_IO_IOS_TUPLE

#include "../util/traits.hpp"

template <class... Ts>
auto &operator>>(tifa_libs::istream_c auto &is, std::tuple<Ts...> &p) NE {
  std::apply([&](Ts &...ts) NE { ((is >> ts), ...); }, p);
  return is;
}
template <class... Ts>
auto &operator<<(tifa_libs::ostream_c auto &os, std::tuple<Ts...> CR p) NE {
  std::apply([&, n = 0](Ts const &...ts) mutable NE { ((os << ts << (++n != sizeof...(Ts) ? " " : "")), ...); }, p);
  return os;
}

#endif