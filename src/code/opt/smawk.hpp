#ifndef TIFALIBS_OPT_SMAWK
#define TIFALIBS_OPT_SMAWK

#include "../util/util.hpp"

namespace tifa_libs::opt {

//! $h(r) = argmin_i a_{r,i}$ MUST be non-decreasing
// a: $[0, n) \times [0, m)$
// @param f: f(u32, u32, u32) -> bool
// f(r, x, y): $a_{r,x}\leq a_{r,y}$
template <class Ft>
constexpr vec<u32> smawk(u32 n, u32 m, Ft&& f) {
  vec<u32> ans(n);
  auto run = [&](auto&& run, u32 u, u32 d, u32 l, u32 r) -> void {
    if (u == d) return;
    assert(l < r);
    const u32 rmid = (u + d) / 2;
    u32 cm = l;
    for (u32 col = l + 1; col < r; ++col)
      if (!f(rmid, cm, col)) cm = col;
    ans[rmid] = cm;
    run(run, u, rmid, l, cm + 1);
    run(run, rmid + 1, d, cm, r);
  };
  run(run, 0, n, 0, m);
  return ans;
}

}  // namespace tifa_libs::opt

#endif