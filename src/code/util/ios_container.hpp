#ifndef TIFA_LIBS_UTIL_IOS_CONTAINER
#define TIFA_LIBS_UTIL_IOS_CONTAINER

#include "traits.hpp"

template <class T, std::enable_if_t<tifa_libs::is_container<T>::value> * = nullptr>
std::istream &operator>>(std::istream &is, T &x) {
  for (auto &i : x) is >> i;
  return is;
}
template <class T, std::enable_if_t<tifa_libs::is_container<T>::value> * = nullptr>
std::ostream &operator<<(std::ostream &os, T const &x) {
  if (x.begin() == x.end()) return os;
  auto it = x.begin();
  os << *it++;
  for (; it != x.end(); ++it) os << ' ' << *it;
  return os;
}

#endif