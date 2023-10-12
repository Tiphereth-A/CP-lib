#ifndef TIFALIBS_POLY_SQRT
#define TIFALIBS_POLY_SQRT

#include "../math/qresidue.hpp"
#include "poly_inv.hpp"
#include "poly_shr.hpp"
#include "poly_shl.hpp"

namespace tifa_libs::math {

namespace polysqrt_detail_ {
template <class T>
constexpr bool sqrt_(poly<T> const &p, poly<T> &ans, size_t n) {
  using mint = typename T::value_type;
  if (n == 1) {
    auto qres = qresidue(p[0].val(), mint::mod());
    if (!qres.has_value()) return false;
    ans[0] = std::min<i64>(qres.value(), mint::mod() - qres.value());
    return true;
  }
  if (!sqrt_(p, ans, (n + 1) / 2)) return false;
  poly<T> sA = p;
  sA.resize(n);
  ans.resize(ans.size() * 2);
  auto _ = poly_inv(ans * 2);
  ans.conv(ans);
  ans.resize(n);
  (ans += sA).conv(_);
  ans.resize(n);
  return true;
}
}  // namespace polysqrt_detail_

template <class T>
inline std::optional<poly<T>> poly_sqrt(poly<T> p) {
  poly<T> ans;
  size_t n = p.size();
  size_t cnt = std::find_if(p.data().begin(), p.data().end(), [](auto const &x) { return x.val() > 0; }) - p.data().begin();
  if (cnt == n) return p;
  if (cnt & 1) return {};
  p = poly_shr(p, cnt);
  p.strip();
  if (bool _ = polysqrt_detail_::sqrt_(p, ans, p.size()); !_) return {};
  ans.resize(n);
  ans = poly_shl(ans, cnt / 2);
  return ans;
}

}  // namespace tifa_libs::math

#endif