#ifndef TIFALIBS_POLY_POLY_DIVMOD
#define TIFALIBS_POLY_POLY_DIVMOD

#include "poly_div.hpp"

namespace tifa_libs::math {

template <class T>
std::pair<poly<T>, poly<T>> poly_divmod(poly<T> const &p, poly<T> const &q) {
  u32 n = p.size(), m = q.size();
  if (n < m) return {poly<T>(), p};
  auto d = poly_div(p, q);
  d.strip();
  auto r = d;
  r.conv(q);
  r.resize(m - 1);
  r = p - r;
  r.resize(m - 1);
  r.strip();
  return {d, r};
}

}  // namespace tifa_libs::math

#endif