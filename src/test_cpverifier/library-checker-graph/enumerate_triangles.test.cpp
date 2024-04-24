#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_triangles"

#include "../../code/graph/ringenum3.hpp"
// clang-format off
#include "../../code/io/ios_pair.hpp"
#include "../../code/io/ios_container.hpp"
// clang-format on

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vecu x(n);
  std::cin >> x;
  vecpt<u32> edges(m);
  std::cin >> edges;
  u64 ans = 0;
  auto func = [&](u32 u, u32 v, u32 w) { ans = (ans + (u128)x[u] * x[v] * x[w]) % 998244353; };
  tifa_libs::graph::ringenum3(n, edges, func);
  std::cout << ans << '\n';
  return 0;
}
