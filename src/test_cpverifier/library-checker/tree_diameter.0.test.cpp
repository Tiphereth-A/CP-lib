#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "../../code/graph/path.hpp"
#include "../../code/tree/diameter_w.hpp"
#include "../../code/util/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  tifa_libs::graph::tree<u64> tr(n);
  for (u32 i = 1, u, v, w; i < n; ++i) {
    std::cin >> u >> v >> w;
    tr.add_edge(u, v, (u64)w);
  }
  auto [u, v, w] = tifa_libs::graph::tree_diameter_w(tr);
  auto p = tifa_libs::graph::path(tr, u, v).value();
  std::cout << w << ' ' << p.size() << '\n';
  std::cout << p << '\n';
  return 0;
}
