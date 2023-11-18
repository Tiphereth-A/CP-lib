#ifndef TIFA_LIBS_UTIL_IOS_PAIR
#define TIFA_LIBS_UTIL_IOS_PAIR

#include "util.hpp"

template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) { return is >> p.first >> p.second; }
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) { return os << p.first << ' ' << p.second; }

#endif