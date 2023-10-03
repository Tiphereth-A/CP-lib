#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/conv_mtt.hpp"

using mint = tifa_libs::math::mint_s63<1000000007>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, m;
  std::cin >> n >> m;
  tifa_libs::vec<mint> a(n), b(m);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  auto c = tifa_libs::math::conv_mtt(a, b);
  for (size_t i = 0; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
