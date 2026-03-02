#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include "../../../src/comb/seq/bernoulli/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md, __LINE__>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin_uint >> n;
  tifa_libs::fout << tifa_libs::math::gen_bernoulli<poly>(n);
  return 0;
}
