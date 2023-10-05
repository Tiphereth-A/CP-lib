#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "../../code/str/manacher.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s;
  std::cin >> s;
  auto ans = tifa_libs::str::manacher(s);
  for (size_t i = 0; i < ans.size(); ++i) std::cout << ans[i] << " \n"[i + 1 == ans.size()];
  return 0;
}
