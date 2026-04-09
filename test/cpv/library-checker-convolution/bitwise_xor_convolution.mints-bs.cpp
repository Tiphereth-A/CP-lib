#define AUTO_GENERATED
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bitwise_xor_convolution
#include "../../../src/conv/xor/lib.hpp"
#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/math/ds/mint/md/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = mint_bs<MOD>;

int main() {
  u32 n;
  tifa_libs::fin_uint >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto& i : a) tifa_libs::fin_uint >> i;
  for (auto& i : b) tifa_libs::fin_uint >> i;
  tifa_libs::fout << tifa_libs::conv_xor(a, b) << '\n';
  return 0;
}
