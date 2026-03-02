#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "../../../src/conv/and/lib.hpp"
#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;

int main() {
  u32 n;
  tifa_libs::fin_uint >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto& i : a) tifa_libs::fin_uint >> i;
  for (auto& i : b) tifa_libs::fin_uint >> i;
  tifa_libs::fout << tifa_libs::math::conv_and(a, b) << '\n';
  return 0;
}
