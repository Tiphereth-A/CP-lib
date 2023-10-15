#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include "../../code/conv/conv_xor.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u64> a(1 << n), b(1 << n);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  auto c = tifa_libs::math::conv_xor(a, b);
  for (size_t i = 0; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
