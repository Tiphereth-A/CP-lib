// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_2_C"

#include "../../../src/ds/heap/d_ary/lib.hpp"
#include "../../../src/util/alias/others/lib.hpp"

using namespace tifa_libs;
CEXP int D = 4;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vveci v(n);
  flt_ (u32, i, 0, q) {
    u32 op, t;
    std::cin >> op >> t;
    if (op == 0) {
      i32 x;
      std::cin >> x;
      v[t].push_back(x);
      push_dary_heap<D>(begin(v[t]), end(v[t]));
    } else {
      if (v[t].empty()) continue;
      if (op == 1) {
        std::cout << v[t].front() << '\n';
      } else {
        pop_dary_heap<D>(begin(v[t]), end(v[t]));
        v[t].pop_back();
      }
    }
  }
  return 0;
}
