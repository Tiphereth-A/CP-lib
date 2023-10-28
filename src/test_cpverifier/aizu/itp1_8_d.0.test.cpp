#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/all/ITP1_8_D"

#include "../../code/str/kmp.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s, p;
  std::cin >> s >> p;
  s += s;
  std::cout << (tifa_libs::str::kmp(p, s).empty() ? "No" : "Yes") << '\n';
  return 0;
}
