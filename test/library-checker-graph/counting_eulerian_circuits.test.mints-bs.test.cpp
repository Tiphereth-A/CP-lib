#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/counting_eulerian_circuits/"

#include "../../include/comb/gen_fact.hpp"
#include "../../include/graph/alist.hpp"
#include "../../include/graph/euler_trail.hpp"
#include "../../include/graph/kirchhoff.hpp"
#include "../../include/lalg/ge_mat.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_bs.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  auto fact = math::gen_fact<mint>(m + 1);
  graph::alist<true> g(n);
  u32 start = 0;
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
    start = u;
  }
  if (!graph::is_eulerian(g)) {
    std::cout << "0\n";
    return 0;
  }
  vecb vis(n);
  auto f = [&](auto &&f, u32 x) -> void {
    for (auto v : g[x])
      if (!vis[v]) vis[v] = 1, f(f, v);
  };
  vis[start] = 1, f(f, start);
  vecu ids(n, -1_u32), inv_ids;
  u32 cnt_ids = 0;
  flt_ (u32, i, 0, n)
    if (vis[i]) ids[i] = cnt_ids++, inv_ids.push_back(i);
  graph::amat<mint> mat(cnt_ids);
  flt_ (u32, id, 0, cnt_ids) {
    auto &tos = g[inv_ids[id]];
    if (tos.empty()) continue;
    tifa_libs::sort(tos);
    u32 cnt = 1, pre = tos[0];
    flt_ (u32, j, 1, (u32)tos.size())
      if (tos[j] != pre) mat.set_arc(id, ids[pre], cnt), pre = tos[j], cnt = 1;
      else ++cnt;
    mat.set_arc(id, ids[pre], cnt);
  }
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&](math::matrix<mint> &A, bool clear_u) { return math::ge_mat<mint, decltype(is_0), true>(A, is_0, clear_u); };
  mint ans = graph::kirchhoff<true>(mat, ids[start], ge);
  flt_ (u32, i, 0, cnt_ids)
    if (g.deg_out[inv_ids[i]]) ans *= fact[g.deg_out[inv_ids[i]] - 1];
  std::cout << ans << '\n';
  return 0;
}