#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_2_C"

#include "../../code/ds/d_ary_heap.hpp"

CEXP int D = 3;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  vvec<i32> v(n);
  flt_ (u32, i, 0, q) {
    u32 op, t;
    std::cin >> op >> t;
    if (op == 0) {
      i32 x;
      std::cin >> x;
      v[t].push_back(x);
      tifa_libs::ds::push_dary_heap<D>(v[t].begin(), v[t].end());
    } else {
      if (v[t].empty()) continue;
      if (op == 1) {
        std::cout << v[t].front() << '\n';
      } else {
        tifa_libs::ds::pop_dary_heap<D>(v[t].begin(), v[t].end());
        v[t].pop_back();
      }
    }
  }
  return 0;
}
