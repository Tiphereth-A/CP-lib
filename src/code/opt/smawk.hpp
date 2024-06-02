#ifndef TIFALIBS_OPT_SMAWK
#define TIFALIBS_OPT_SMAWK

#include "../util/util.hpp"

namespace tifa_libs::opt {

//! $h(r) = argmin_i a_{r,i}$ MUST be non-decreasing
// a: $[0, n) \times [0, m)$
// @param f: f(u32, u32, u32) -> bool
// f(r, x, y): $a_{r,x}\leq a_{r,y}$
template <class Ft>
CEXP vecu smawk(u32 n, u32 m, Ft&& f) {
  vecu ans(n);
  auto g = [&](auto&& g, u32 u, u32 d, u32 l, u32 r) -> void {
    if (u == d) return;
    assert(l < r);
    const u32 rmid = (u + d) / 2;
    u32 cm = l;
    flt_ (u32, col, l + 1, r)
      if (!f(rmid, cm, col)) cm = col;
    ans[rmid] = cm, g(g, u, rmid, l, cm + 1), g(g, rmid + 1, d, cm, r);
  };
  g(g, 0, n, 0, m);
  return ans;
}

}  // namespace tifa_libs::opt

#endif