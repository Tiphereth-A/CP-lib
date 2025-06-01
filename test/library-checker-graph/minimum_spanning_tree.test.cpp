#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree/"

#include "../../include/edh/discretization.hpp"
#include "../../include/graph/kruskal.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  vec<edge_tu> e(m);
  map<edge_tu, u32> id;
  u32 cnt = 0;
  for (auto& [w, u, v] : e) {
    std::cin >> u >> v >> w;
    id[{u, v, w}] = id[{v, u, w}] = ++cnt;
  }
  std::ranges::sort(e);
  auto tr = graph::kruskal(e, n);
  u64 ret = 0;
  vecu es;
  flt_ (u32, i, 0, n)
    for (auto [to, w] : tr.g[i]) {
      ret += w;
      es.push_back(id[{i, to, w}] - 1);
    }
  std::cout << ret / 2 << '\n'
            << uniq(es) << '\n';
  return 0;
}