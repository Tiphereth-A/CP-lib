#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../../src/comb/binom/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md, __LINE__>;

int main() {
  u32 t, MOD;
  fin_uint >> t >> MOD;
  mint::set_mod(MOD);
  math::binom<mint> mCn(10'000'001);
  while (t--) {
    i64 n, k;
    fin_uint >> n >> k;
    fout << (MOD < 1e7 ? mCn.lucas(n, k) : mCn.mCn(n, k)) << '\n';
  }
  return 0;
}
