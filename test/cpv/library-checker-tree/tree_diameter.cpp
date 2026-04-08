// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/graph/path/lib.hpp"
#include "../../../src/io/container/lib.hpp"
#include "../../../src/tree/dfs/diam/lib.hpp"
#include "../../../src/tree/ds/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  alist<u64> g(n);
  for (u32 i = 1, u, v, w; i < n; ++i) {
    std::cin >> u >> v >> w;
    g.add_arc(u, v, (u64)w), g.add_arc(v, u, (u64)w);
  }
  tree tr(g);
  auto [u, v, w] = tree_diam(tr);
  auto p = path(g, u, v).value();
  std::cout << w << ' ' << p.size() << '\n';
  std::cout << p << '\n';
  return 0;
}
