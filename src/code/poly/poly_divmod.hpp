#ifndef TIFALIBS_POLY_DIVMOD
#define TIFALIBS_POLY_DIVMOD

#include "poly_div.hpp"

namespace tifa_libs::math {

template <class T>
inline std::pair<poly<T>, poly<T>> poly_divmod(poly<T> const &p, poly<T> const &q) {
  auto d = poly_div(p, q), r = d;
  r.conv(q, q.size() - 1);
  r = p - r;
  r.resize(q.size() - 1);
  return {d, r};
}

}  // namespace tifa_libs::math

#endif