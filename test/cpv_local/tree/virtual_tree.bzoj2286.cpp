// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/2286

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/tree/virtual_tree/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 n;
  fin_uint >> n;
  vecu sign(n), min_(n);
  using Tw = u32;
  graph::treew<Tw> trw(n);
  for (u32 i = 1, u, v, w; i < n; ++i) fin_uint >> u >> v >> w, --u, --v, trw.add_arc(u, v, w), trw.add_arc(v, u, w);
  auto dfs = [&](auto&& dfs, u32 u, u32 fa, u32 min__) -> void {
    min_[u] = min__;
    for (auto [to, w] : trw.g[u])
      if (to != fa) dfs(dfs, to, u, std::min(min__, w));
  };
  dfs(dfs, 0, 0, INT32_MAX);
  graph::virtual_tree vt(trw);
  u32 m, k;
  fin_uint >> m;
  flt_ (u32, i, 0, m) {
    fin_uint >> k;
    vecu a(k);
    for (auto& x : a) fin_uint >> x, --x, sign[x] = 1;
    vt.build(a);
    auto dp = [&](auto&& dp, u32 u) -> u64 {
      if (sign[u]) return min_[u];
      u64 ret = 0;
      for (auto [to, w] : vt.vt.g[u]) ret += dp(dp, to);
      retif_((u), std::min(u64(min_[u]), ret), ret);
    };
    fout << dp(dp, 0) << '\n';
    flt_ (u32, i, 0, k) sign[a[i]] = 0;
  }
}
