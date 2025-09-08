#ifndef TIFALIBS_OPT_KNAPSACK_MIXED_HUGE
#define TIFALIBS_OPT_KNAPSACK_MIXED_HUGE

#include "../util/alias_others.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::opt {

//@param a a[i]={value, weight, count}
//@param W max weight
//@return max total value while total weight <= W
template <int_c T>
CEXP T knapsack_mixed_huge(vec<pt3<T>> a, T W) NE {
  const u32 n = (u32)a.size();
  assert(n < 500);
  const u32 lim = [k = max(n, 50_u32)] { return k * k * k + 1; }();
  vec<T> dp(lim + 1, to_uint_t<T>(-1) / 2 - 1);
  dp[0] = 0;
  for (auto& [v, w, num] : a) {
    T have = min(num, (T)n);
    num -= have;
    for (T k = 1; k = min(have, k), have; have -= k, k <<= 1)
      for (u32 j = lim - 1; (T)j >= v * k; --j) dp[j] = min(dp[j], dp[j - v * k] + w * k);
  }
  vecu id(n);
  std::iota(begin(id), end(id), 0), sort(id, [&](auto x, auto y) { return a[x]._0 * a[y]._1 > a[y]._0 * a[x]._1; });
  T ans = 0;
  flt_ (u32, j, 0, lim + 1) {
    if (W < dp[j]) continue;
    T rest = W - dp[j], now = j;
    for (auto i : id) {
      auto [v, w, num] = a[i];
      T div = min(num, rest / w);
      rest -= div * w, now += div * v;
    }
    ans = max(ans, now);
  }
  return ans;
}

}  // namespace tifa_libs::opt

#endif