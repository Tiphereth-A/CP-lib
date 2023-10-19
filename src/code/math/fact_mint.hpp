#ifndef TIFA_LIBS_MATH_FACT_MINT
#define TIFA_LIBS_MATH_FACT_MINT

#include "../poly/poly_ctsh.hpp"

namespace tifa_libs::math {

template <class polydata, class mint = typename polydata::value_type>
inline mint fact_mint(u64 n) {
  if (n <= 1) return 1;
  using poly_t = poly<polydata>;
  u64 v = 1;
  while (v * v < n) v *= 2;
  mint iv = mint(v).inv();
  poly_t g{1, v + 1};
  for (u64 d = 1; d != v; d *= 2) {
    poly_t g1 = poly_ctsh(g, mint(d) * iv), g2 = poly_ctsh(g, mint(d * v + v) * iv), g3 = poly_ctsh(g, mint(d * v + d + v) * iv);
    for (u64 i = 0; i <= d; ++i) g[i] *= g1[i], g2[i] *= g3[i];
    std::copy(g2.data().begin(), g2.data().end() - 1, std::back_inserter(g.data()));
  }
  mint res = 1;
  u64 i = 0;
  while (i + v <= n) res *= g[i / v], i += v;
  while (i < n) res *= ++i;
  return res;
}

}  // namespace tifa_libs::math

#endif