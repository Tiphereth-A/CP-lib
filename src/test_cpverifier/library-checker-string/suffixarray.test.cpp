#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../../code/str/suffix_array.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  u32 n = (u32)s.size();
  s = " " + s;
  tifa_libs::str::suffixarray sa(s);
  fle_ (u32, i, 1, n) std::cout << sa.sa[i] - 1 << " \n"[i == n];
  return 0;
}
