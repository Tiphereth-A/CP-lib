#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_G"

#include "../../include/ds/fenwick_rr.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  ds::fenwick_rr<u64> tr(n + 2);
  flt_ (u32, i, 0, q) {
    u32 op, u, v, w;
    std::cin >> op >> u >> v;
    ++u, ++v;
    if (op) std::cout << tr.sum(u, v) << '\n';
    else (std::cin >> w), tr.add(u, v, w);
  }
  return 0;
}
