#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/all/ITP1_9_A"

#include "../../include/str/kmp.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s, p, _;
  std::cin >> p;
  while (std::cin >> _, _ != "END_OF_TEXT") {
    for (char &c : _)
      if (isalpha(c)) c = (char)tolower(c);
    (s += _) += ' ';
  }
  std::cout << str::kmp(' ' + p + ' ', ' ' + s + ' ').size() << '\n';
  return 0;
}
