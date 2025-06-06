#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "../../include/graph/dinic.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 l, r, m;
  std::cin >> l >> r >> m;
  u32 s = l + r, t = l + r + 1;
  graph::dinic big(l + r + 2);
  flt_ (u32, i, 0, l) big.add(s, i, 1);
  flt_ (u32, i, 0, r) big.add(i + l, t, 1);
  for (u32 i = 0, u, v; i < m; ++i) std::cin >> u >> v, big.add(u, v + l, 1);
  std::cout << big.get(s, t) << '\n';
  flt_ (u32, i, 0, l) {
    u32 ret = s;
    for (auto v : big.e[i])
      if (v.w == 0 && l <= v.to && v.to < l + r) {
        ret = v.to - l;
        break;
      }
    if (ret != s) std::cout << i << ' ' << ret << '\n';
  }
  return 0;
}
