#define PROBLEM "https://www.luogu.com.cn/problem/P8435"

#include "../../code/graph/e_bcc.hpp"


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  struct EW {
    u32 inv;
  };
  tifa_libs::graph::adjlist<void, EW> e(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    if(u == v) continue;
    --u, --v;
    u32 tem1 = e[u].size(), tem2 = e[v].size();
    e.add_arc(u, v, EW{tem2});
    e.add_arc(v, u, EW{tem1});
  }
  tifa_libs::graph::e_bcc<void, EW> bcc(e);
  std::cout << bcc.id << '\n';
  for (u32 i = 0; i < bcc.id; ++i) {
    std::cout << bcc.belongs[i].size() << ' ';
    for (auto x : bcc.belongs[i])
      std::cout << x + 1 << ' ';
    std::cout << '\n';
  }
  return 0;
}