#pragma once

#include "../../math/qpow/rpow/lib.hpp"
#include "../ds/poly_c/lib.hpp"

namespace tifa_libs {

// @brief Chirp Z-Transform
// @return {f(a*c^0), f(a*c^1), ..., f(a*c^{m-1})}
template <poly_c poly_t>
auto czt_fps(poly_t f, TPN poly_t::val_t c, u32 m = -1_u32, TPN poly_t::val_t a = 1) NE {
  using mint = TPN poly_t::val_t;
  static rpow rp, irp;
  if (!~m) m = (u32)f.size();
  retif_((f.empty() || !m) [[unlikely]], poly_t{});
  const u32 n = (u32)f.size();
  if (a != 1) {
    mint x = 1;
    flt_ (u32, i, 0, n) f[i] *= x, x *= a;
  }
  if (c == 0) {
    poly_t ans(m, f[0]);
    ans[0] = std::reduce(begin(f), end(f), mint{});
    return ans;
  }
  const u32 mod = (u32)mint::mod();
  if (c.val() == irp.base()) rp.swap(irp);
  rp.reset(c.val(), mod), irp.reset(c.inv().val(), mod);
  poly_t cc(m + n), icc(max(m, n));
  cc[0] = icc[0] = 1;
  flt_ (u32, i, 1, m + n) cc[i] = rp(u32((i * (i - 1_u64) / 2) % (mod - 1)));
  flt_ (u32, i, 1, max(m, n)) icc[i] = irp(u32((i * (i - 1_u64) / 2) % (mod - 1)));
  flt_ (u32, i, 1, n) f[i] *= icc[i];
  reverse(f), f.conv(cc, n + m);
  poly_t ans(begin(f) + ((isz)n - 1), begin(f) + (isz(n + m) - 1));
  flt_ (u32, i, 1, m) ans[i] *= icc[i];
  return ans;
}

}  // namespace tifa_libs
