#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree/"

#include "../../include/ds/cartesian_tree.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  veci a(n);
  for (auto &x : a) std::cin >> x;
  tifa_libs::ds::cartesian_tree tr(a);
  flt_ (u32, i, 0, n) std::cout << tr.t[i].fa << ' ';
  return 0;
}
