#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/all/ITP1_8_D"

#include "../../include/str/kmp.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s, p;
  std::cin >> s >> p;
  s += s;
  std::cout << (str::kmp(p, s).empty() ? "No" : "Yes") << '\n';
  return 0;
}
