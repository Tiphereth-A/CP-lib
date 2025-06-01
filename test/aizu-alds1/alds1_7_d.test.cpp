#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_7_D"

#include "../../include/io/ios_container.hpp"
#include "../../include/tree/btree_make_post_pi.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu a(n), b(n);
  std::cin >> a >> b;
  std::cout << graph::btree_make_post_pi(a, b) << '\n';
  return 0;
}
