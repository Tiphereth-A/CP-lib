#ifndef TIFALIBS_GRAPH_CHROM_NUM
#define TIFALIBS_GRAPH_CHROM_NUM

#include "../bit/parity.hpp"
#include "../math/mul_mod_s.hpp"
#include "alist.hpp"

namespace tifa_libs::graph {
namespace chrom_num_impl_ {
template <u32 mod>
CEXP u32 calc(u32 n, vecpt<i32> hist) {
  fle_ (u32, c, 1, n) {
    i64 _ = 0;
    for (auto& [i, x] : hist) _ += (x = (i32)math::mul_mod_s(x, i, mod));
    if (_ % (i32)mod) return c;
  }
  return n;
}
}  // namespace chrom_num_impl_

template <bool with_deg>
CEXP u32 chrom_num(alist<with_deg> CR fg) {
  auto&& g = fg.g;
  u32 n = (u32)g.size();
  vecu adj(n), dp(1 << n);
  flt_ (u32, i, 0, n)
    for (u32 to : g[i]) adj[i] |= 1 << to, adj[to] |= 1 << i;
  dp[0] = 1;
  for (u32 i = 1; i < (1u << n); ++i) {
    u32 k = i & (i - 1);
    dp[i] = dp[k] + dp[k & ~adj[(u32)std::countr_zero(i)]];
  }
  vec<i32> _((1 << n) + 1);
  for (u32 i = 0; i < (1u << n); ++i) _[dp[i]] += bit::parity(i) ? -1 : 1;
  vecpt<i32> hist;
  for (u32 i = 1; i <= (1u << n); ++i)
    if (_[i]) hist.emplace_back(i, _[i]);
  return min(chrom_num_impl_::calc<1000000021>(n, hist), chrom_num_impl_::calc<1000000033>(n, hist));
}

}  // namespace tifa_libs::graph

#endif