#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_2_64"

#include "../../code/conv/karatsuba.hpp"
#include "../../code/util/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<u64> a(n), b(m);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  std::cout << tifa_libs::math::karatsuba(a, b) << '\n';
  return 0;
}
