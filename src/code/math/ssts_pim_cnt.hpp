#ifndef TIFALIBS_MATH_SSTS_PIM_CNT
#define TIFALIBS_MATH_SSTS_PIM_CNT

#include "../comb/gen_inv.hpp"
#include "../poly/exp_fps.hpp"

namespace tifa_libs::math {

template <class poly, class T, std::same_as<typename poly::value_type> mint>
poly ssts_pim_cnt(vec<T> const& s, u32 t, vec<mint> const& inv) {
  std::map<T, u32> cnt;
  for (auto&& i : s) ++cnt[i];
  poly p(t + 1);
  for (u32 x = 1; x <= t; ++x)
    for (u32 d = 1; d <= t / x; ++d)
      if (d & 1) p[d * x] += mint(cnt[x]) * inv[d];
      else p[d * x] -= mint(cnt[x]) * inv[d];
  return exp_fps(p);
}
template <class poly, class T>
poly ssts_pim_cnt(vec<T> const& s, u32 t) {
  using mint = typename poly::value_type;
  return ssts_pim_cnt<poly, T, mint>(s, t, gen_inv<mint>(t + 1));
}

}  // namespace tifa_libs::math

#endif