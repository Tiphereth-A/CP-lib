#ifndef TIFALIBS_MATH_SSTS_PIM_CNT
#define TIFALIBS_MATH_SSTS_PIM_CNT

#include "../comb/gen_inv.hpp"
#include "../poly/poly_exp.hpp"

namespace tifa_libs::math {

template <class T, class U, class mint = typename T::value_type>
poly<T> ssts_pim_cnt(vec<U> const& s, u32 t, vec<mint> const& inv) {
  std::map<U, u32> cnt;
  for (auto&& i : s) ++cnt[i];
  poly<T> p(t + 1);
  for (u32 x = 1; x <= t; ++x)
    for (u32 d = 1; d <= t / x; ++d)
      if (d & 1) p[d * x] += mint(cnt[x]) * inv[d];
      else p[d * x] -= mint(cnt[x]) * inv[d];
  return poly_exp(p);
}
template <class T, class U, class mint = typename T::value_type>
poly<T> ssts_pim_cnt(vec<U> const& s, u32 t) { return ssts_pim_cnt<T, U, mint>(s, t, gen_inv<mint>(t + 1)); }

}  // namespace tifa_libs::math

#endif