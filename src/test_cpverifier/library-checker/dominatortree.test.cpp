#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree/"

#include "../../code/graph/domtree.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, s;
  std::cin >> n >> m >> s;
  tifa_libs::graph::alist<> g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  tifa_libs::graph::domtree dt(g);
  auto res = dt.get_domtree(s);
  for (u32 i = 0; i < n; ++i) std::cout << (i32)res[i] << " \n"[i == n - 1];
  return 0;
}