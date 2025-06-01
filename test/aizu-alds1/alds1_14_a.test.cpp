#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_A"

#include "../../include/str/kmp.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s, p;
  std::cin >> s >> p;
  auto _ = str::kmp(p, s);
  for (auto i : _) std::cout << i << '\n';
  return 0;
}
