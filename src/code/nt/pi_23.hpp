#ifndef TIFALIBS_MATH_PI_23
#define TIFALIBS_MATH_PI_23

#include "../math/div64.hpp"
#include "../math/ikth_root.hpp"
#include "../math/isqrt.hpp"
#include "prime_seq.hpp"

namespace tifa_libs::math {

constexpr u64 pi_23(u64 n) {
  if (n < 2) return 0;
  u64 n2 = isqrt(n), n3 = ikth_root(n, 3), n6 = ikth_root(n, 6), n23 = n / n3;
  auto prime = prime_seq((u32)n2 + 1000);
  u32 pidx = 0;
  u64 pi = 0;
  vecu64 ns;
  ns.reserve(n2 * 2 + 2);
  ns.push_back(0);
  for (u32 i = 1; i <= n2; ++i) ns.push_back(div_u64d(n, i));
  for (u64 i = ns.back() - 1; i; --i) ns.push_back(i);
  u32 nsz = (u32)ns.size();
  vecu64 h = ns;
  for (auto &i : h) --i;
  while (prime[pidx] <= n6) {
    u32 p = prime[pidx];
    u64 p2 = (u64)p * p;
    for (u64 i = 1, n = ns[i]; i < nsz && n >= p2; n = ns[++i]) h[i] -= h[i * p <= n2 ? i * p : nsz - div_u64d(n, p)] - pi;
    ++pidx, ++pi;
  }
  vec<i32> bit(nsz - n3);
  auto dfs = [&](auto &&rec, u64 cur, u32 pid, bool flag) -> void {
    if (flag)
      if (u64 id = cur <= n2 ? nsz - cur : div_u64d(n, cur); id > n3)
        for (id -= n3; id; id -= id & -id) --bit[id];
    for (u32 dst = pid; cur * prime[dst] < n23; ++dst) rec(rec, cur * prime[dst], dst, true);
  };
  while (prime[pidx] <= n3) {
    u32 p = prime[pidx];
    u64 p2 = (u64)p * p;
    for (u64 i = 1; i <= n3; ++i) {
      if (p2 > ns[i]) break;
      u64 id = i * p <= n2 ? i * p : nsz - div_u64d(ns[i], p);
      i64 _ = (i64)h[id];
      if (id > n3)
        for (id -= n3; id < bit.size(); id += id & -id) _ += bit[id];
      h[i] -= (u64)_ - pi;
    }
    dfs(dfs, p, pidx, false);
    ++pidx, ++pi;
  }
  for (usz i = bit.size() - 1; i; --i)
    if (usz j = i + (i & -i); j < bit.size()) bit[i] += bit[j];
  for (u32 i = 1; i < bit.size(); ++i) h[i + n3] += (u64)bit[i];
  while (prime[pidx] <= n2) {
    u32 p = prime[pidx];
    u64 p2 = (u64)p * p;
    for (u64 i = 1, n = ns[i]; i < nsz && n >= p2; n = ns[++i]) h[i] -= h[i * p <= n2 ? i * p : nsz - div_u64d(n, p)] - pi;
    ++pidx, ++pi;
  }
  return h[1];
}

}  // namespace tifa_libs::math

#endif