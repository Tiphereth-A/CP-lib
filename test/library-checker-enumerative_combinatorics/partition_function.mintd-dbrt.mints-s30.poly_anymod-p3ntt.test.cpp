#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../../include/comb/gen_partition.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_dbrt.hpp"
#include "../../include/math/mint_s30.hpp"
#include "../../include/poly/poly3ntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_dbrt, __LINE__>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_s30, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_s30, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_s30, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin >> n;
  tifa_libs::fout << tifa_libs::math::gen_partition<poly>(n);
  return 0;
}
