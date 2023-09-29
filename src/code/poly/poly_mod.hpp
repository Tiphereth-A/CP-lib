#ifndef TIFALIBS_POLY_MOD
#define TIFALIBS_POLY_MOD

#include "poly_divmod.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_mod(poly<T> const &p, poly<T> const &q) { return poly_divmod(p, q).second; }

}  // namespace tifa_libs::math

#endif