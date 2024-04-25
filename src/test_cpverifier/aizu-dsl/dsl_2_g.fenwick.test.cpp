#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_G"

#include "../../code/ds/fenwick_rr.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::fenwick_rr<u64> tr(n + 2);
  flt_ (u32, i, 0, q) {
    u32 op, u, v, w;
    std::cin >> op >> u >> v;
    ++u, ++v;
    if (op) std::cout << tr.sum(u, v) << '\n';
    else (std::cin >> w), tr.add(u, v, w);
  }
  return 0;
}
