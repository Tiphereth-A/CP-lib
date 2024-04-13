#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C"

#include "../../code/ds/depq.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  strn s;
  vec<u32> v;
  while (std::cin >> s) {
    if (s == "end") break;
    if (s[0] == 'i') {
      u32 x;
      std::cin >> x;
      v.push_back(x);
      tifa_libs::ds::push_minmax_heap(v.begin(), v.end());
    } else {
      tifa_libs::ds::pop_minmax_heap_max(v.begin(), v.end());
      std::cout << v.back() << '\n';
      v.pop_back();
    }
  }
  return 0;
}
