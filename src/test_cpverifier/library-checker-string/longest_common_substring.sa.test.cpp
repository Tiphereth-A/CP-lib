#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include "../../code/str/lcs_sa.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s, t;
  std::cin >> s >> t;
  auto [a, b, c, d] = tifa_libs::str::lcs_sa(s, t);
  std::cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
  return 0;
}
