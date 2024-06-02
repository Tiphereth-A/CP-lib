#define PROBLEM "https://judge.yosupo.jp/problem/two_sat/"

#include "../../code/graph/sat2.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s >> s;
  u32 n, m;
  std::cin >> n >> m;
  i32 u, v, w;
  tifa_libs::graph::sat2 s2(n);
  flt_ (u32, i, 0, m) {
    std::cin >> u >> v >> w;
    bool fu = u > 0, fv = v > 0;
    s2.add((u32)abs(u) - 1, fu, (u32)abs(v) - 1, fv);
  }
  auto ans = s2.solve();
  if (!ans) {
    std::cout << "s UNSATISFIABLE\n";
    return 0;
  }
  std::cout << "s SATISFIABLE\nv";
  for (i32 i = 0; (u32)i < n; ++i) std::cout << ' ' << (ans.value()[(u32)i] ? (i + 1) : -(i + 1));
  std::cout << " 0\n";
  return 0;
}