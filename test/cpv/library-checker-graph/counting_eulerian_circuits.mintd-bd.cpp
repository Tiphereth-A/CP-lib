#define AUTO_GENERATED
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/counting_eulerian_circuits/
#include "../../../src/comb/seq/fact/lib.hpp"
#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/graph/ds/amat/lib.hpp"
#include "../../../src/graph/ds/info/lib.hpp"
#include "../../../src/graph/euler_trail/lib.hpp"
#include "../../../src/graph/kirchhoff/lib.hpp"
#include "../../../src/lalg/mat/ge/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/bd/lib.hpp"

using namespace tifa_libs;
using mint = mint_bd<__LINE__>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  auto fact = gen_fact<mint>(m + 1);
  alist<void, degin_tag, degout_tag, arc_cnt_tag> g(n);
  u32 start = 0;
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
    start = u;
  }
  if (!is_eulerian(g)) {
    std::cout << "0\n";
    return 0;
  }
  vecb vis(n);
  auto f = [&](auto&& f, u32 x) -> void {
    for (auto v : g[x])
      if (!vis[v]) vis[v] = 1, f(f, v);
  };
  vis[start] = 1, f(f, start);
  vecu ids(n, -1_u32), inv_ids;
  u32 cnt_ids = 0;
  flt_ (u32, i, 0, n)
    if (vis[i]) ids[i] = cnt_ids++, inv_ids.push_back(i);
  amat<mint> mat(cnt_ids);
  flt_ (u32, id, 0, cnt_ids) {
    auto& tos = g[inv_ids[id]];
    if (tos.empty()) continue;
    tifa_libs::sort(tos);
    u32 cnt = 1, pre = tos[0];
    flt_ (u32, j, 1, (u32)tos.size())
      if (tos[j] != pre) mat.add_arc(id, ids[pre], cnt), pre = tos[j], cnt = 1;
      else ++cnt;
    mat.add_arc(id, ids[pre], cnt);
  }
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&](matrix<mint>& A, bool clear_u) { return ge_mat<mint, decltype(is_0), true>(A, is_0, clear_u); };
  mint ans = kirchhoff<true>(mat, ids[start], ge);
  flt_ (u32, i, 0, cnt_ids)
    if (g.dout[inv_ids[i]]) ans *= fact[g.dout[inv_ids[i]] - 1];
  std::cout << ans << '\n';
  return 0;
}