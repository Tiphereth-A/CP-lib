#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include "../../../src/str/lcs_sa/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s, t;
  std::cin >> s >> t;
  auto [a, b, c, d] = str::lcs_sa(s, t);
  std::cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
  return 0;
}
