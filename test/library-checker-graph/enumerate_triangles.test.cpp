#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_triangles"

#include "../../include/graph/ringenum3.hpp"
// clang-format off
#include "../../include/io/ios_pair.hpp"
#include "../../include/io/ios_container.hpp"
// clang-format on

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  vecu x(n);
  std::cin >> x;
  vecptu edges(m);
  std::cin >> edges;
  u64 ans = 0;
  auto func = [&](u32 u, u32 v, u32 w) { ans = u32((ans + (u128)x[u] * x[v] * x[w]) % 998244353); };
  graph::ringenum3(n, edges, func);
  std::cout << ans << '\n';
  return 0;
}
