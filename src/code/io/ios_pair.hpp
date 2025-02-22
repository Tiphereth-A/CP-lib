#ifndef TIFALIBS_IO_IOS_PAIR
#define TIFALIBS_IO_IOS_PAIR

#include "../util/traits.hpp"

template <class T, class U>
auto &operator>>(tifa_libs::istream_c auto &is, std::pair<T, U> &p) NE { return is >> p.first >> p.second; }
template <class T, class U>
auto &operator<<(tifa_libs::ostream_c auto &os, std::pair<T, U> CR p) NE { return os << p.first << ' ' << p.second; }

#endif