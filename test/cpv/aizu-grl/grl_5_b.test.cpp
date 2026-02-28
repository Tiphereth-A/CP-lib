#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_B"

#include "../../../src/tree/dfs/height/lib.hpp"
#include "../../../src/tree/ds/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  graph::treew<u32> tr(n);
  for (u32 i = 1, u, v, w; i < n; ++i) {
    std::cin >> u >> v >> w;
    tr.add_arc(u, v, w), tr.add_arc(v, u, w);
  }
  auto v = graph::tree_height(tr);
  for (auto&& i : v) std::cout << i << '\n';
  return 0;
}
