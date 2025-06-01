#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "../../include/graph/path.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/tree/diam.hpp"
#include "../../include/tree/tree.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  graph::treew<u64> tr(n);
  for (u32 i = 1, u, v, w; i < n; ++i) {
    std::cin >> u >> v >> w;
    tr.add_arc(u, v, (u64)w), tr.add_arc(v, u, (u64)w);
  }
  auto [u, v, w] = graph::tree_diam(tr);
  auto p = graph::path(tr, u, v).value();
  std::cout << w << ' ' << p.size() << '\n';
  std::cout << p << '\n';
  return 0;
}
