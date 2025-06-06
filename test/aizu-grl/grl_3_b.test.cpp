#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_B"

#include "../../include/graph/v_bcc.hpp"
#include "../../include/io/ios_pair.hpp"

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
  graph::v_bcc<false, true, false> bcc(g);
  std::ranges::sort(bcc.ecut, {}, [](auto CR x) { return std::minmax(x.first, x.second); });
  for (auto [u, v] : bcc.ecut) std::cout << std::minmax(u, v) << '\n';
  return 0;
}
