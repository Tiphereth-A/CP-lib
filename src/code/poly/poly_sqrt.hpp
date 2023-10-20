#ifndef TIFALIBS_POLY_SQRT
#define TIFALIBS_POLY_SQRT

#include "../math/qresidue.hpp"
#include "poly_inv.hpp"
#include "poly_shl.hpp"
#include "poly_shr.hpp"

namespace tifa_libs::math {

template <class T>
inline std::optional<poly<T>> poly_sqrt(poly<T> p, usz n = 0) {
  using mint = typename T::value_type;
  if (!n) n = p.size();
  usz cnt = std::find_if(p.data().begin(), p.data().begin() + n, [](auto const &x) { return x.val() > 0; }) - p.data().begin();
  if (cnt == n) return p.pre(n);
  if (cnt & 1) return {};
  poly<T> ans{0};
  p = poly_shr(p, cnt);
  if (auto qres = qresidue(p[0].val(), mint::mod()); !qres.has_value()) return {};
  else ans[0] = std::min(qres.value(), mint::mod() - qres.value());
  mint i2 = mint(2).inv();
  for (usz i = 1; i < n; i *= 2) ans = (ans + p.pre(i * 2) * poly_inv(ans, i * 2)) * i2;
  ans.resize(n);
  return poly_shl(ans, cnt / 2);
}

}  // namespace tifa_libs::math

#endif