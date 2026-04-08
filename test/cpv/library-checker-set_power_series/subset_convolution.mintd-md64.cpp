#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"

#include "../../../src/conv/subset/lib.hpp"
#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/md64/lib.hpp"

using namespace tifa_libs;
using mint = mint_md64<__LINE__>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin_uint >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto& i : a) tifa_libs::fin_uint >> i;
  for (auto& i : b) tifa_libs::fin_uint >> i;
  tifa_libs::conv_subset<mint, 20> cvs;
  tifa_libs::fout << cvs.conv(a, b) << '\n';
  return 0;
}
