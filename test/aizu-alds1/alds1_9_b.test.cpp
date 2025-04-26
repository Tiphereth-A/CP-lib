#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_B"

#include "../../include/ds/d_ary_heap.hpp"
#include "../../include/io/ios_container.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  veci v(n);
  std::cin >> v;
  tifa_libs::ds::make_dary_heap<2>(v.begin(), v.end());
  std::cout << ' ' << v << '\n';
  return 0;
}
