#define PROBLEM "https://www.luogu.com.cn/problem/P3369"

#include "../../code/ds/fhq_treap.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n;
  std::cin >> n;
  tifa_libs::ds::fhq_treap<i32> treap(n);
  for (size_t i = 0, opt; i < n; ++i) {
    i32 x;
    std::cin >> opt >> x;
    if (opt == 1) treap.insert(x);
    else if (opt == 2) treap.erase(x);
    else if (opt == 3) std::cout << treap.w_que_rk(x) << '\n';
    else if (opt == 4) std::cout << treap.rk_que_w(treap.root, size_t(x)) << '\n';
    else if (opt == 5) std::cout << treap.pre_w(x) << '\n';
    else std::cout << treap.suf_w(x) << '\n';
  }
  return 0;
}
