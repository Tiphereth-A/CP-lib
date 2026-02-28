#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_B"

#include "../../../src/ds/heap/d_ary/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  veci v(n);
  std::cin >> v;
  ds::make_dary_heap<2>(begin(v), end(v));
  std::cout << ' ' << v << '\n';
  return 0;
}
