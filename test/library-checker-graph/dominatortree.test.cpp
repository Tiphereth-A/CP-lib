#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree/"

#include "../../include/graph/alist.hpp"
#include "../../include/graph/domtree.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, s;
  std::cin >> n >> m >> s;
  graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  graph::domtree dt(g);
  auto res = dt.get_domtree(s);
  flt_ (u32, i, 0, n) std::cout << (i32)res[i] << " \n"[i == n - 1];
  return 0;
}