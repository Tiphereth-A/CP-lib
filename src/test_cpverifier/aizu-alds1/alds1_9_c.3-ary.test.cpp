#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C"

#include "../../code/ds/d_ary_heap.hpp"

CEXP int D = 3;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  vecu v;
  while (std::cin >> s) {
    if (s == "end") break;
    if (s[0] == 'i') {
      u32 x;
      std::cin >> x;
      v.push_back(x);
      tifa_libs::ds::push_dary_heap<D>(v.begin(), v.end());
    } else {
      tifa_libs::ds::pop_dary_heap<D>(v.begin(), v.end());
      std::cout << v.back() << '\n';
      v.pop_back();
    }
  }
  return 0;
}
