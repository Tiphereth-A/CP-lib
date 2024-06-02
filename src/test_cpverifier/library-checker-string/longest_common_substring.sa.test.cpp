#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include "../../code/io/ios_tuple.hpp"
#include "../../code/str/lcs_sa.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s, t;
  std::cin >> s >> t;
  std::cout << tifa_libs::str::lcs_sa(s, t) << '\n';
  return 0;
}
