#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/counting_spanning_tree_directed"

#include "../../include/fast/rsort32.hpp"
#include "../../include/graph/alist.hpp"
#include "../../include/graph/kirchhoff.hpp"
#include "../../include/lalg/ge_mat.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, MOD>;

int main() {
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
