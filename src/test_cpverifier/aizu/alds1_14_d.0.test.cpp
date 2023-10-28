#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D/"

#include "../../code/str/suffix_array.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string t, s;
  std::cin >> t;
  t = " " + t;
  u32 n;
  std::cin >> n;
  tifa_libs::str::suffixarray sa(t);
  for (u32 i = 0; i < n; ++i) {
    std::cin >> s;
    s = " " + s;
    std::cout << bool(sa.frequency(s)) << '\n';
  }
  return 0;
}
