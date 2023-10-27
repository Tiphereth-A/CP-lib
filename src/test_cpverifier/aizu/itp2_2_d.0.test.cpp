#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_2_D"

#include "../../code/util/ios_container.hpp"
#include "../../code/util/ndvec.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ndvec<2, i32> nv(n, 0);
  i32 x;
  for (u32 i = 0, op, s, t; i < q; ++i) {
    std::cin >> op >> t;
    switch (op) {
      case 0:
        std::cin >> x;
        nv[t].push_back(x);
        break;
      case 1:
        std::cout << nv[t] << '\n';
        break;
      case 2:
        std::cin >> s;
        nv[s].insert(nv[s].end(), nv[t].begin(), nv[t].end());
        nv[t].clear();
    }
  }
  return 0;
}
