#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree/"

#include "../../code/ds/cartesian_tree.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<i32> a(n);
  for(auto &x: a) std::cin >> x;
  tifa_libs::ds::cartesian_tree tr(a);
  for(u32 i = 0; i < n; ++ i) std::cout << tr.t[i].fa << ' ';
  return 0;
}
