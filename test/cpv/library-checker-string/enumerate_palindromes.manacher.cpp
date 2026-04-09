// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_palindromes
#include "../../../src/io/container/lib.hpp"
#include "../../../src/str/manacher/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  std::cout << manacher(s) << '\n';
  return 0;
}
