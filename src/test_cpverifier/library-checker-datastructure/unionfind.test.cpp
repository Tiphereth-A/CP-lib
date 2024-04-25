#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../../code/ds/dsu_basic.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::dsu_basic dsu(n + 1);
  fle_ (u32, i, 1, q) {
    u32 t, u, v;
    std::cin >> t >> u >> v;
    if (t == 0)
      dsu.merge(u, v);
    else
      std::cout << dsu.same(u, v) << '\n';
  }
  return 0;
}
