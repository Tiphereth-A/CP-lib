#define PROBLEM "https://judge.yosupo.jp/problem/lyndon_factorization"

#include "../../include/io/ios_container.hpp"
#include "../../include/str/lyndon.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  std::cout << str::duval(s) << '\n';
  return 0;
}
