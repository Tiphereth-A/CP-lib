#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../../code/ds/dsu_basic.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::dsu_basic dsu(n + 1);
  for (size_t i = 1, t, u, v; i <= q; ++i) {
    std::cin >> t >> u >> v;
    if (t == 0) dsu.merge(u, v);
    else std::cout << dsu.same_group(u, v) << '\n';
  }
  return 0;
}
