#ifndef TIFALIBS_MATH_FACT_MINT
#define TIFALIBS_MATH_FACT_MINT

#include "../poly/ctsh_fps.hpp"

namespace tifa_libs::math {

template <class poly>
CEXP auto fact_mint(u64 n) NE {
  using mint = TPN poly::val_t;
  if (n <= 1) return mint(1);
  if (n >= mint::mod()) return mint(0);
  u64 v = 1;
  while (v * v < n) v *= 2;
  const mint iv = mint(v).inv();
  poly g{1, v + 1};
  for (u64 d = 1; d != v; d *= 2) {
    poly g1 = ctsh_fps(g, mint(d) * iv),
         g2 = ctsh_fps(g, mint(d * v + v) * iv),
         g3 = ctsh_fps(g, mint(d * v + d + v) * iv);
    flt_ (u32, i, 0, (u32)d + 1) g[i] *= g1[i], g2[i] *= g3[i];
    copy(g2.begin(), g2.end() - 1, std::back_inserter(g));
  }
  mint res = 1;
  u64 i = 0;
  while (i + v <= n) res *= g[u32(i / v)], i += v;
  while (i < n) res *= ++i;
  return res;
}

}  // namespace tifa_libs::math

#endif