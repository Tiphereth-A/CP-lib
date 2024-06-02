#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_A"

#include "../../code/str/kmp.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s, p;
  std::cin >> s >> p;
  auto _ = tifa_libs::str::kmp(p, s);
  for (auto i : _) std::cout << i << '\n';
  return 0;
}
