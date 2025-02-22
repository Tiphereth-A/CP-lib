#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include "../../code/conv/conv_xor.hpp"
#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/math/mint_d31.hpp"
#include "../../code/io/ios_container.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto &i : a) tifa_libs::fin >> i;
  for (auto &i : b) tifa_libs::fin >> i;
  tifa_libs::fout << tifa_libs::math::conv_xor(a, b) << '\n';
  return 0;
}
