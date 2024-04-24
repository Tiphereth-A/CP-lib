#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_B"

#include "../../code/ds/d_ary_heap.hpp"
#include "../../code/io/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<i32> v(n);
  std::cin >> v;
  tifa_libs::ds::make_dary_heap<2>(v.begin(), v.end());
  std::cout << ' ' << v << '\n';
  return 0;
}
