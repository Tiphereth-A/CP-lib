#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "../../include/io/ios_container.hpp"
#include "../../include/str/manacher.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  std::cout << tifa_libs::str::manacher(s) << '\n';
  return 0;
}
