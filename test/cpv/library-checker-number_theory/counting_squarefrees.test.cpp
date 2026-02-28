#define PROBLEM "https://judge.yosupo.jp/problem/counting_squarefrees"

#include "../../../src/nt/mfsum/sqrfree_cnt/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << math::sqrfree_cnt(n) << '\n';
  return 0;
}
