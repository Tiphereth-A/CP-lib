// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include "../../../src/ds/dq/p/lib.hpp"
#include "../../../src/util/alias/others/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 _tests = 1;
  flt_ (u32, _test, 1, _tests + 1) {
    u32 n, q;
    std::cin >> n >> q;
    vec<int> a(n);
    for (auto& x : a) std::cin >> x;
    make_minmax_heap(begin(a), end(a));
    while (q--) {
      int t;
      std::cin >> t;
      if (t == 0) {
        int x;
        std::cin >> x;
        a.push_back(x);
        push_minmax_heap(begin(a), end(a));
      } else if (t == 1) {
        pop_minmax_heap_min(begin(a), end(a));
        std::cout << a.back() << '\n';
        a.pop_back();
      } else {
        pop_minmax_heap_max(begin(a), end(a));
        std::cout << a.back() << '\n';
        a.pop_back();
      }
    }
  }
  return 0;
}
