#ifndef TIFALIBS_GRAPH_CHROM_NUM
#define TIFALIBS_GRAPH_CHROM_NUM

#include "../bit/parity.hpp"
#include "../math/mul_mod.hpp"
#include "../util/alias_others.hpp"
#include "../util/traits_graph.hpp"

namespace tifa_libs::graph {
namespace chrom_num_impl_ {
template <u32 mod>
CEXP u32 calc(u32 n, vecpti hist) NE {
  flt_ (u32, c, 1, n + 1) {
    i64 _ = 0;
    for (auto& [i, x] : hist) _ += (x = (i32)math::mul_mod_s(x, i, mod));
    if (_ % (i32)mod) return c;
  }
  return n;
}
}  // namespace chrom_num_impl_

CEXP u32 chrom_num(alist_c auto CR g) NE {
  const u32 n = g.size();
  vecu adj(n), dp(1 << n);
  flt_ (u32, i, 0, n)
    for (auto to : g[i]) adj[i] |= 1 << (u32)to, adj[(u32)to] |= 1 << i;
  dp[0] = 1;
  flt_ (u32, i, 1, 1u << n) {
    u32 k = i & (i - 1);
    dp[i] = dp[k] + dp[k & ~adj[(u32)std::countr_zero(i)]];
  }
  veci _((1 << n) + 1);
  flt_ (u32, i, 0, 1u << n) _[dp[i]] += bit::parity(i) ? -1 : 1;
  vecpti hist;
  flt_ (u32, i, 1, (1u << n) + 1)
    if (_[i]) hist.emplace_back(i, _[i]);
  return min(chrom_num_impl_::calc<1000000021>(n, hist), chrom_num_impl_::calc<1000000033>(n, hist));
}

}  // namespace tifa_libs::graph

#endif