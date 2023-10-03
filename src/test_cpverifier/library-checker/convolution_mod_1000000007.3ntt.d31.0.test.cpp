#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/math/mint_d31.hpp"
#include "../../code/poly/conv_3ntt.hpp"

using mint0 = tifa_libs::math::mint_d31<-167772161>;
using mint1 = tifa_libs::math::mint_d31<-469762049>;
using mint2 = tifa_libs::math::mint_d31<-754974721>;

int main() {
  mint0::set_mod(167772161);
  mint1::set_mod(469762049);
  mint2::set_mod(754974721);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, m;
  std::cin >> n >> m;
  tifa_libs::vec<tifa_libs::u64> a(n), b(m);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  auto c = tifa_libs::math::conv_3ntt<mint0, mint1, mint2>(a, b, 1000000007);
  for (size_t i = 0; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
