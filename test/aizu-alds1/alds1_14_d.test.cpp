#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D/"

#include "../../include/str/suffix_array.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn t, s;
  std::cin >> t;
  t = " " + t;
  u32 n;
  std::cin >> n;
  str::suffixarray sa(t);
  flt_ (u32, i, 0, n) {
    std::cin >> s;
    s = " " + s;
    std::cout << bool(sa.frequency(s)) << '\n';
  }
  return 0;
}
