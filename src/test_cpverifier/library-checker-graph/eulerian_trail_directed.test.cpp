#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_directed"

#include "../../code/graph/euler_trail.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    u32 n, m;
    std::cin >> n >> m;
    vecpt<u32> e(m);
    for (auto& [u, v] : e) std::cin >> u >> v;
    if (auto res = tifa_libs::graph::euler_trail<true>(n, e); !res.has_value()) {
      std::cout << "No\n";
    } else {
      std::cout << "Yes\n";
      auto et = res.value();
      flt_ (u32, i, 0, (u32)et.size()) std::cout << et[i].first << " \n"[i + 1 == et.size()];
      if (et.size() == 1) std::cout << '\n';
      flt_ (u32, i, 1, (u32)et.size()) std::cout << et[i].second << " \n"[i + 1 == et.size()];
    }
  }
  return 0;
}
