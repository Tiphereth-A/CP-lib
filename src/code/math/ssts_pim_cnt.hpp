#ifndef TIFALIBS_MATH_SSTS_PIM_CNT
#define TIFALIBS_MATH_SSTS_PIM_CNT

#include "../comb/gen_inv.hpp"
#include "../poly/exp_fps.hpp"

namespace tifa_libs::math {

template <class poly, class T, std::same_as<TPN poly::val_t> mint>
poly ssts_pim_cnt(vec<T> CR s, u32 t, vec<mint> CR inv) {
  std::map<T, u32> cnt;
  for (auto&& i : s) ++cnt[i];
  poly p(t + 1);
  fle_ (u32, x, 1, t)
    fle_ (u32, d, 1, t / x)
      if (d & 1) p[d * x] += mint(cnt[x]) * inv[d];
      else p[d * x] -= mint(cnt[x]) * inv[d];
  return exp_fps(p);
}
template <class poly, class T>
poly ssts_pim_cnt(vec<T> CR s, u32 t) {
  using mint = TPN poly::val_t;
  return ssts_pim_cnt<poly, T, mint>(s, t, gen_inv<mint>(t + 1));
}

}  // namespace tifa_libs::math

#endif