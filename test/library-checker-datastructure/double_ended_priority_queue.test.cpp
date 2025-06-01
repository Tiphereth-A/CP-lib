#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include "../../include/ds/depq.hpp"
#include "../../include/util/alias_others.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 _tests = 1;
  flt_ (u32, _test, 1, _tests + 1) {
    u32 n, q;
    std::cin >> n >> q;
    vec<int> a(n);
    for (auto &x : a) std::cin >> x;
    ds::make_minmax_heap(a.begin(), a.end());
    while (q--) {
      int t;
      std::cin >> t;
      if (t == 0) {
        int x;
        std::cin >> x;
        a.push_back(x);
        ds::push_minmax_heap(a.begin(), a.end());
      } else if (t == 1) {
        ds::pop_minmax_heap_min(a.begin(), a.end());
        std::cout << a.back() << '\n';
        a.pop_back();
      } else {
        ds::pop_minmax_heap_max(a.begin(), a.end());
        std::cout << a.back() << '\n';
        a.pop_back();
      }
    }
  }
  return 0;
}
