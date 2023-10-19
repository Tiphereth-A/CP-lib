#ifndef TIFA_LIBS_MATH_PI_23
#define TIFA_LIBS_MATH_PI_23

#include "ikth_root.hpp"
#include "isqrt.hpp"
#include "linear_p_seive.hpp"

namespace tifa_libs::math {

inline u64 pi_23(u64 n) {
  if (n < 2) return 0;
  static auto div = [](u64 n, u64 p) -> u64 { return (u64)((double)n / (double)p); };
  u64 n6, n3, n2, n23, nsz;
  vec<u64> ns, h;
  vec<u32> bit;
  n2 = isqrt(n);
  n3 = ikth_root(n, 3);
  while (n3 * n3 * n3 > n) n3--;
  while ((n3 + 1) * (n3 + 1) * (n3 + 1) <= n) n3++;
  n6 = isqrt(n3);
  n23 = n / n3;
  auto prime = linear_p_seive((u32)n2 + 1000);
  u32 pidx = 0;
  u64 pi = 0;
  ns.reserve(n2 * 2 + 2);
  ns.push_back(0);
  for (usz i = 1; i <= n2; ++i) ns.push_back(div(n, i));
  for (usz i = ns.back() - 1; i; --i) ns.push_back(i);
  nsz = ns.size();
  std::copy(ns.begin(), ns.end(), std::back_inserter(h));
  for (auto &i : h) --i;

  while (prime[pidx] <= n6) {
    u32 p = prime[pidx];
    u64 p2 = (u64)p * p;
    for (u64 i = 1, n = ns[i]; i < nsz && n >= p2; n = ns[++i]) h[i] -= h[i * p <= n2 ? i * p : nsz - div(n, p)] - pi;
    ++pidx, ++pi;
  }

  bit.resize(nsz - n3);
  auto dfs = [&](auto rec, u64 cur, u32 pid, bool flag) -> void {
    if (flag) {
      // if cur > N^{1/2} :
      // cur <= floor(N / id)
      // -> cur * id + n = N, n < id < cur
      // -> id <= floor(N / cur)
      u64 id = cur <= n2 ? nsz - cur : div(n, cur);
      // decrease h[N3] ~ h[id]
      if (id > n3)
        for (id -= n3; id; id -= id & -id) --bit[id];
    }
    for (u32 dst = pid; cur * prime[dst] < n23; ++dst) rec(rec, cur * prime[dst], dst, true);
  };

  while (prime[pidx] <= n3) {
    u32 p = prime[pidx];
    u64 p2 = (u64)p * p;
    for (usz i = 1; i <= n3; ++i) {
      if (p2 > ns[i]) break;
      u64 id = i * p <= n2 ? i * p : nsz - div(ns[i], p), sm = h[id];
      if (id > n3)
        for (id -= n3; id < bit.size(); id += id & -id) sm += bit[id];
      h[i] -= sm - pi;
    }
    dfs(dfs, p, pidx, false);
    ++pidx, ++pi;
  }

  for (usz i = bit.size() - 1; i; --i)
    if (usz j = i + (i & -i); j < bit.size()) bit[i] += bit[j];
  for (usz i = 1; i < bit.size(); ++i) h[i + n3] += bit[i];

  while (prime[pidx] <= n2) {
    u32 p = prime[pidx];
    u64 p2 = (u64)p * p;
    for (usz i = 1, n = ns[i]; i < nsz && n >= p2; n = ns[++i]) h[i] -= h[i * p <= n2 ? i * p : nsz - div(n, p)] - pi;
    ++pidx, ++pi;
  }

  return h[1];
}

}  // namespace tifa_libs::math

#endif