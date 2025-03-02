#ifndef TIFALIBS_OPT_LARSCH
#define TIFALIBS_OPT_LARSCH

#include "../util/traits.hpp"

namespace tifa_libs::opt {

template <arithm_c T, class Func>
requires requires(Func f, u32 x, u32 y) { {f(x,y)}->std::same_as<T>; }
CEXP vec<T> larsch(u32 n, Func&& w, T inf = inf_v<T>) NE {
  vec<T> dp(n + 1, inf);
  vecu x(n + 1);
  auto chk = [&](u32 from, u32 to) {
    if (from >= to) return;
    if (T cost = w(from, to); dp[from] + cost < dp[to]) dp[to] = dp[from] + cost, x[to] = from;
  };
  auto f = [&](auto&& f, u32 l, u32 r) -> void {
    if (l + 1 >= r) return;
    u32 m = l + (r - l) / 2;
    for (u32 i = x[l]; i <= x[r]; i++) chk(i, m);
    f(f, l, m);
    for (u32 i = l + 1; i <= m; i++) chk(i, r);
    f(f, m, r);
  };
  dp[0] = 0, chk(0, n), f(f, 0, n);
  return dp;
};

}  // namespace tifa_libs::opt

#endif