#ifndef TIFALIBS_OPT_KNAPSACK_01
#define TIFALIBS_OPT_KNAPSACK_01

#include "../util/alias_others.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::opt {

//@param a a[i]={value, weight}
//@param W max weight
//@return max total value while total weight <= W
template <int_c T>
CEXP T knapsack_01(vecpt<T> CR a, T W) NE {
  const T vs = [k = std::views::keys(a)] { return std::reduce(k.begin(), k.end(), T{}); }();
  const T _1 = W, _2 = vs,
          _3 = T(a.size() >= 100 ? inf_v<T> : (T)min((u64)inf_v<T>, 1_u64 << ((a.size() + 1) / 2))),
          _min = min({_1, _2, _3});
  assert(0_isz <= (isz)_min && (usz)_min * a.size() < (usz)1e9);
  if (_min == _1) {
    vec<T> dp(W + 1);
    for (auto [s, t] : a)
      for (u32 j = u32(W - t); (i32)j >= 0; --j) dp[j + t] = max(dp[j + t], dp[j] + s);
    return max(dp);
  } else if (const T inf = to_uint_t<T>(-1) / 2 - 1; _min == _2) {
    vec<T> dp(vs + 1, inf);
    dp[0] = 0;
    for (auto [s, t] : a)
      for (u32 j = u32(vs - s); (i32)j >= 0; --j) dp[j + s] = min(dp[j + s], dp[j] + t);
    T ans = 0;
    flt_ (T, i, 0, T(vs + 1))
      if (dp[i] <= W) ans = max(ans, i);
    return ans;
  } else {
    auto f = [&](u32 l, u32 r) {
      vecpt<T> res(1 << (r - l));
      res[0] = {0, 0};
      flt_ (u32, i, 0, r - l)
        flt_ (u32, j, 0, 1 << i) {
          auto&& [v, w] = a[l + i];
          res[je + j] = {res[j].first + w, res[j].second + v};
        }
      sort(res);
      flt_ (u32, i, 1, (u32)res.size()) res[i].second = max(res[i].second, res[i - 1].second);
      return res;
    };
    auto l = f(0, (u32)a.size() / 2), r = f((u32)a.size() / 2, (u32)a.size());
    reverse(l), r.emplace_back(inf, inf);
    T ans = 0;
    u32 id = -1_u32;
    for (auto& [t, s] : l) {
      while (t + r[id + 1].first <= W) ++id;
      if (~id) ans = max(ans, s + r[id].second);
    }
    return ans;
  }
}

}  // namespace tifa_libs::opt

#endif