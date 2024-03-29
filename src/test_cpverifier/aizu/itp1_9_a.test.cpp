#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/all/ITP1_9_A"

#include "../../code/str/kmp.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  strn s, p, _;
  std::cin >> p;
  while (std::cin >> _, _ != "END_OF_TEXT") {
    for (char &c : _)
      if (isalpha(c)) c = (char)tolower(c);
    (s += _) += ' ';
  }
  std::cout << tifa_libs::str::kmp(' ' + p + ' ', ' ' + s + ' ').size() << '\n';
  return 0;
}
