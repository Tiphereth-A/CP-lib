#ifndef TIFALIBS_POLY_POLY_CZT
#define TIFALIBS_POLY_POLY_CZT

#include "../math/rpow.hpp"

namespace tifa_libs::math {

// @brief Chirp Z-Transform
// @return {f(a*c^0), f(a*c^1), ..., f(a*c^{m-1})}
template <class poly, std::same_as<typename poly::value_type> mint>
poly poly_czt(poly f, mint c, u32 m = -1_u32, mint a = 1) {
  static rpow rp, irp;
  if (m == -1_u32) m = f.size();
  if (f.data().empty() || !m) return poly{};
  u32 n = f.size();
  if (a != 1) {
    mint x = 1;
    for (u32 i = 0; i < n; ++i) f[i] *= x, x *= a;
  }
  if (c == 0) {
    poly ans(m, f[0]);
    ans[0] = std::reduce(f.data().begin(), f.data().end(), mint{});
    return ans;
  }
  assert(mint::mod() <= u64(-1_u32));
  const u32 mod = (u32)mint::mod();
  if (c.val() == irp.base()) rp.swap(irp);
  rp.reset(c.val(), mod);
  irp.reset(c.inv().val(), mod);
  poly cc(m + n), icc(std::max(m, n));
  cc[0] = icc[0] = 1;
  for (u32 i = 1; i < m + n; ++i) cc[i] = rp((i * (i - 1_u64) / 2) % (mod - 1));
  for (u32 i = 1; i < std::max(m, n); ++i) icc[i] = irp((i * (i - 1_u64) / 2) % (mod - 1));
  for (u32 i = 1; i < n; ++i) f[i] *= icc[i];
  std::reverse(f.data().begin(), f.data().end());
  f.conv(cc, n + m);
  poly ans(f.data().begin() + ((isz)n - 1), f.data().begin() + (isz(n + m) - 1));
  for (u32 i = 1; i < m; ++i) ans[i] *= icc[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif