#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/str/z_func.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s;
  std::cin >> s;
  auto ans = tifa_libs::str::z_function(s);
  for (size_t i = 0; i < ans.size(); ++i) std::cout << ans[i] << " \n"[i + 1 == ans.size()];
  return 0;
}
