#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C"

#include "../../include/ds/depq.hpp"
#include "../../include/util/alias_others.hpp"

using namespace tifa_libs;
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
      ds::push_minmax_heap(begin(v), end(v));
    } else {
      ds::pop_minmax_heap_max(begin(v), end(v));
      std::cout << v.back() << '\n';
      v.pop_back();
    }
  }
  return 0;
}
