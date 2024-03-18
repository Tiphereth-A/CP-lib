#ifndef TIFALIBS_MATH_FACT_MINT
#define TIFALIBS_MATH_FACT_MINT

#include "../poly/poly_ctsh.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr auto fact_mint(u64 n) {
  using mint = typename poly::value_type;
  if (n <= 1) return mint(1);
  if (n >= mint::mod()) return mint(0);
  u64 v = 1;
  while (v * v < n) v *= 2;
  mint iv = mint(v).inv();
  poly g{1, v + 1};
  for (u64 d = 1; d != v; d *= 2) {
    poly g1 = poly_ctsh<poly, mint>(g, mint(d) * iv), g2 = poly_ctsh<poly, mint>(g, mint(d * v + v) * iv), g3 = poly_ctsh<poly, mint>(g, mint(d * v + d + v) * iv);
    for (u32 i = 0; i <= d; ++i) g[i] *= g1[i], g2[i] *= g3[i];
    std::copy(g2.data().begin(), g2.data().end() - 1, std::back_inserter(g.data()));
  }
  mint res = 1;
  u64 i = 0;
  while (i + v <= n) res *= g[u32(i / v)], i += v;
  while (i < n) res *= ++i;
  return res;
}

}  // namespace tifa_libs::math

#endif