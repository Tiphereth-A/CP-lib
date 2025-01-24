#ifndef TIFALIBS_IO_IOS_CONTAINER
#define TIFALIBS_IO_IOS_CONTAINER

#include "../util/traits.hpp"

template <tifa_libs::container_c T>
std::istream &operator>>(std::istream &is, T &x) NE {
  for (auto &i : x) is >> i;
  return is;
}
template <tifa_libs::container_c T>
std::ostream &operator<<(std::ostream &os, T CR x) NE {
  if (x.begin() == x.end()) return os;
  auto it = x.begin();
  for (os << *it++; it != x.end(); ++it) os << ' ' << *it;
  return os;
}

#endif