#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../../include/str/suffix_array.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  u32 n = (u32)s.size();
  s = " " + s;
  str::suffixarray sa(s);
  flt_ (u32, i, 1, n + 1) std::cout << sa.sa[i] - 1 << " \n"[i == n];
  return 0;
}
