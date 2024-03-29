#define PROBLEM "https://judge.yosupo.jp/problem/lyndon_factorization"

#include "../../code/io/ios_container.hpp"
#include "../../code/str/lyndon.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  strn s;
  std::cin >> s;
  std::cout << tifa_libs::str::duval(s) << '\n';
  return 0;
}
