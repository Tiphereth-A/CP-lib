#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_B"

#include "../../code/tree/height.hpp"
#include "../../code/tree/treew.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  tifa_libs::graph::treew<u32> tr(n);
  for (u32 i = 1, u, v, w; i < n; ++i) {
    std::cin >> u >> v >> w;
    tr.add_arc(u, v, w), tr.add_arc(v, u, w);
  }
  auto v = tifa_libs::graph::tree_height(tr);
  for (auto &&i : v) std::cout << i << '\n';
  return 0;
}
