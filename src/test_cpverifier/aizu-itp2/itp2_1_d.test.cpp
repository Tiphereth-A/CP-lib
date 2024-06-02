#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_1_D"

#include "../../code/io/ios_container.hpp"
#include "../../code/util/ndvec.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ndvec<2, i32> nv(n, 0u);
  i32 x;
  for (u32 i = 0, op, t; i < q; ++i) {
    std::cin >> op >> t;
    switch (op) {
      case 0:
        std::cin >> x;
        nv[t].push_back(x);
        break;
      case 1: std::cout << nv[t] << '\n'; break;
      case 2: nv[t].clear();
    }
  }
  return 0;
}
