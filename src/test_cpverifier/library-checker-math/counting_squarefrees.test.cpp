#define PROBLEM "https://judge.yosupo.jp/problem/counting_squarefrees"

#include "../../code/nt/sqrfree_cnt.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::sqrfree_cnt(n) << '\n';
  return 0;
}
