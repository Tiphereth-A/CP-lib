#ifndef TIFALIBS_OPT_LARSCH_2D
#define TIFALIBS_OPT_LARSCH_2D

#include "../util/traits.hpp"
#include "smawk.hpp"

namespace tifa_libs::opt {

template <arithm_c T, class Func>
requires requires(Func f, u32 x, u32 y) { {f(x,y)}->std::same_as<T>; }
CEXP vec<T> larsch_2d(u32 n, Func&& w, T inf = inf_v<T>) NE {
  using W = to_bigger_t<T>;
  vec<W> dp(n + 1, inf_v<W>);
  vec<T> ans(n + 1, inf);
  dp[0] = 0;
  auto f = [&](u32 j, u32 i) -> W { return i < j ? dp[i] + w(i, j) : inf_v<W>; };
  flt_ (u32, d, 1, n) {
    auto argmin = smawk(n + 1, n + 1, [&](u32 i, u32 j, u32 k) { return f(i, j) <= f(i, k); });
    for (u32 i = n; i >= d; --i) dp[i] = dp[argmin[i]] + w(argmin[i], i);
    ans[d] = (T)dp[n];
  }
  return ans;
};

}  // namespace tifa_libs::opt

#endif