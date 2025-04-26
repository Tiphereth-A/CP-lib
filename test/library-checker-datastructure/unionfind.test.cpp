#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../../include/ds/dsu_basic.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::dsu_basic dsu(n + 1);
  flt_ (u32, i, 1, q + 1) {
    u32 t, u, v;
    std::cin >> t >> u >> v;
    if (t == 0)
      dsu.merge(u, v);
    else
      std::cout << dsu.same(u, v) << '\n';
  }
  return 0;
}
