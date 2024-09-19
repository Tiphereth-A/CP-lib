#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "../../code/graph/path.hpp"
#include "../../code/io/ios_container.hpp"
#include "../../code/tree/diam.hpp"
#include "../../code/tree/tree.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  tifa_libs::graph::treew<u64> tr(n);
  for (u32 i = 1, u, v, w; i < n; ++i) {
    std::cin >> u >> v >> w;
    tr.add_arc(u, v, (u64)w), tr.add_arc(v, u, (u64)w);
  }
  auto [u, v, w] = tifa_libs::graph::tree_diam(tr);
  auto p = tifa_libs::graph::path(tr, u, v).value();
  std::cout << w << ' ' << p.size() << '\n';
  std::cout << p << '\n';
  return 0;
}
