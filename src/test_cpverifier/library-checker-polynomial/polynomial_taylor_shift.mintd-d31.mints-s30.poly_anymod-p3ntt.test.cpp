#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/poly/tsh_fps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d31.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;
using mint_p3ntt1 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 167772161>;
using mint_p3ntt2 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 469762049>;
using mint_p3ntt3 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  mint c;
  tifa_libs::fin >> n >> c;
  poly a(n);
  tifa_libs::fin >> a;
  tifa_libs::fout << tifa_libs::math::tsh_fps(a, c) << '\n';
  return 0;
}
