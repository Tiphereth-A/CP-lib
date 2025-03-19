#define PROBLEM "https://judge.yosupo.jp/problem/counting_squarefrees"

#include "../../include/nt/sqrfree_cnt.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::sqrfree_cnt(n) << '\n';
  return 0;
}
