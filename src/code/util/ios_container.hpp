#ifndef TIFALIBS_UTIL_IOS_CONTAINER
#define TIFALIBS_UTIL_IOS_CONTAINER

#include "traits.hpp"

template <tifa_libs::container_c T>
std::istream &operator>>(std::istream &is, T &x) {
  for (auto &i : x) is >> i;
  return is;
}
template <tifa_libs::container_c T>
std::ostream &operator<<(std::ostream &os, T const &x) {
  if (x.begin() == x.end()) return os;
  auto it = x.begin();
  os << *it++;
  for (; it != x.end(); ++it) os << ' ' << *it;
  return os;
}

#endif