#ifndef TIFALIBS_IO_PAIR_LIB
#define TIFALIBS_IO_PAIR_LIB

#include "../../util/traits/others/lib.hpp"

namespace tifa_libs {

template <class T, class U>
auto& operator>>(tifa_libs::istream_c auto& is, std::pair<T, U>& p) NE { return is >> p.first >> p.second; }
template <class T, class U>
auto& operator<<(tifa_libs::ostream_c auto& os, std::pair<T, U> CR p) NE { return os << p.first << ' ' << p.second; }

}  // namespace tifa_libs

#endif