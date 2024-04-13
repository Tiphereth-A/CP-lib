#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C"

#include "../../code/ds/d_ary_heap.hpp"

constexpr int D = 2;

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
      tifa_libs::ds::push_dary_heap<D>(v.begin(), v.end());
    } else {
      tifa_libs::ds::pop_dary_heap<D>(v.begin(), v.end());
      std::cout << v.back() << '\n';
      v.pop_back();
    }
  }
  return 0;
}
