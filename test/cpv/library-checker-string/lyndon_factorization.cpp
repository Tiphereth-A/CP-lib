// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lyndon_factorization
#include "../../../src/io/container/lib.hpp"
#include "../../../src/str/lyndon/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  std::cout << duval(s) << '\n';
  return 0;
}
