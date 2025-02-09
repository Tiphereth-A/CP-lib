#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/counting_spanning_tree_directed"

#include "../../code/fast/rsort32.hpp"
#include "../../code/graph/alist.hpp"
#include "../../code/graph/kirchhoff.hpp"
#include "../../code/lalg/ge_mat.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d63.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, r;
  std::cin >> n >> m >> r;
  tifa_libs::graph::alist<true> g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  tifa_libs::graph::amat<mint> mat(n);
  flt_ (u32, id, 0, n) {
    auto &tos = g.g[id];
    if (tos.empty()) continue;
    tifa_libs::sort(tos);
    u32 cnt = 1, pre = tos[0];
    flt_ (u32, j, 1, (u32)tos.size())
      if (tos[j] != pre) {
        mat.set_arc(id, pre, cnt), pre = tos[j], cnt = 1;
      } else ++cnt;
    mat.set_arc(id, pre, cnt);
  }
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&](tifa_libs::math::matrix<mint> &A, bool clear_u) { return tifa_libs::math::ge_mat<mint, decltype(is_0), true>(A, is_0, clear_u); };
  std::cout << tifa_libs::graph::kirchhoff<true>(mat, r, ge) << '\n';
  return 0;
}
