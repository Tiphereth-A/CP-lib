#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/conv/conv_u128.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<u64> a(n), b(m);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  auto c = tifa_libs::math::conv_u128(a, b);
  for (size_t i = 0; i < c.size(); ++i) std::cout << (u32)(c[i] % 1000000007) << " \n"[i + 1 == c.size()];
  return 0;
}
