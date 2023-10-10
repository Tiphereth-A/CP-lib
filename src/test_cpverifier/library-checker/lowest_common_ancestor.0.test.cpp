#include <cstddef>
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../code/tree/tree.hpp"


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n, q;
  std::cin >> n >> q;
  tifa_libs::tree::tree t(n);
  for(size_t i = 1, x; i < n; ++ i) std::cin >> x, t.add(x, i);
  for(size_t i = 0, u, v; i < q; ++ i) {
    std::cin >> u >> v;
    std::cout << t.lca(u, v) << '\n';
  }
  return 0;
}
