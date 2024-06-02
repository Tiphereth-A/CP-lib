#define PROBLEM "https://judge.yosupo.jp/problem/lyndon_factorization"

#include "../../code/io/ios_container.hpp"
#include "../../code/str/lyndon.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  std::cout << tifa_libs::str::duval(s) << '\n';
  return 0;
}
