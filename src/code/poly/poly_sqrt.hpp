#ifndef TIFALIBS_POLY_SQRT
#define TIFALIBS_POLY_SQRT

#include "../math/qresidue.hpp"
#include "poly_inv.hpp"

namespace tifa_libs::math {

namespace polysqrt_detail_ {
template <class T>
constexpr bool sqrt_(poly<T> const &p, poly<T> &ans, size_t n) {
  using mint = typename T::value_type;
  if (n == 1) {
    auto qres = qresidue(p.d[0], p.mod());
    if (!qres.has_value() || qres.value() <= 0) return false;
    ans[0] = std::min<i64>(qres.value(), mint::mod() - qres.value());
    return true;
  }
  if (!sqrt_(ans, (n + 1) / 2)) return false;
  poly<T> sA = p;
  sA.resize(n);
  ans.resize(ans.size() * 2);
  auto _ = poly_inv(ans * 2);
  ans.conv(ans, n);
  ans += sA;
  ans.conv(_, n);
}
}  // namespace polysqrt_detail_

template <class T>
inline std::optional<poly<T>> poly_sqrt(poly<T> const &p) {
  poly<T> ans;
  if (bool _ = polysqrt_detail_::sqrt_(p, ans, p.size()); !_) return {};
  return ans;
}

}  // namespace tifa_libs::math

#endif