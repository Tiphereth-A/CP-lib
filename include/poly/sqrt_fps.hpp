#ifndef TIFALIBS_POLY_SQRT_FPS
#define TIFALIBS_POLY_SQRT_FPS

#include "../nt/qresidue.hpp"
#include "inv_fps.hpp"
#include "shl_fps.hpp"
#include "shr_fps.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto sqrt_fps(poly<ccore, mint, args...> p, u32 n = 0) NE {
  using poly_t = poly<ccore, mint, args...>;
  std::optional<poly_t> ret;
  if (!n) n = (u32)p.size();
  const u32 cnt = u32(find_if(begin(p), begin(p) + n, [](cT_(mint) x) NE { return x.val() != 0; }) - begin(p));
  if (cnt == n) [[unlikely]] {
    ret.emplace(p.pre(n));
    return ret;
  }
  if (cnt & 1) return ret;
  poly_t ans{0};
  p = shr_fps(p, cnt);
  if (auto qres = qresidue(p[0].val(), mint::mod()); !qres) return ret;
  else ans[0] = min(qres.value(), mint::mod() - qres.value());
  auto i2 = mint(2).inv();
  for (u32 i = 1; i < n; i *= 2) ans = (ans + p.pre(i * 2) * inv_fps(ans, i * 2)) * i2;
  ret.emplace(shl_fps(ans.pre(n), cnt / 2));
  return ret;
}

}  // namespace tifa_libs::math

#endif