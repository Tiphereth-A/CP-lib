#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"

#include "../../include/graph/alist.hpp"
#include "../../include/graph/chrom_num.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_edge(u, v);
  }
  std::cout << graph::chrom_num(g) << '\n';
  return 0;
}
