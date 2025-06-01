#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../include/comb/binom.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d31.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_d31, __LINE__>;

int main() {
  u32 t, MOD;
  fin >> t >> MOD;
  mint::set_mod(MOD);
  math::binom<mint> mCn(10'000'001);
  while (t--) {
    i64 n, k;
    fin >> n >> k;
    fout << (MOD < 1e7 ? mCn.lucas(n, k) : mCn.mCn(n, k)) << '\n';
  }
  return 0;
}
