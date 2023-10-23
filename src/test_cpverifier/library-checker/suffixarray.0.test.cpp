#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../../code/str/suffix_array.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s;
  std::cin >> s;
  usz n = s.size();
  s = " " + s;
  auto [sa, rk] = tifa_libs::str::suffixsort(s);
  for (usz i = 1; i <= n; ++i) std::cout << sa[i] - 1 << " \n"[i == n];
  return 0;
}
