#ifndef TIFALIBS_IO_IOS_CONTAINER
#define TIFALIBS_IO_IOS_CONTAINER

#include "../util/traits.hpp"

auto &operator>>(tifa_libs::istream_c auto &is, tifa_libs::container_c auto &x) NE {
  for (auto &i : x) is >> i;
  return is;
}
auto &operator<<(tifa_libs::ostream_c auto &os, tifa_libs::container_c auto CR x) NE {
  if (x.begin() == x.end()) [[unlikely]]
    return os;
  auto it = x.begin();
  for (os << *it++; it != x.end(); ++it) os << ' ' << *it;
  return os;
}

#endif