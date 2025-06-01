#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_cliques/"

#include "../../include/graph/clique_calc.hpp"

using namespace tifa_libs;
CEXP u32 N = 128;
CEXP u32 MOD = 998244353;
using B = std::bitset<N>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  vecuu v(n);
  for (auto& i : v) std::cin >> i;
  arr<B, N> adj;
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    adj[u][v] = adj[v][u] = 1;
  }
  std::cout << (graph::clique_calc(n, adj, [](u64 x, u64 y) { return x + y; }, [&](u64 x, u32 i) { return x * v[i] % MOD; }, 0_u64, 1_u64) + (MOD - 1)) % MOD << '\n';
  return 0;
}