#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include "../../include/conv/conv_xor.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/math/mint_md.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_md.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md, __LINE__>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin_uint >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto &i : a) tifa_libs::fin_uint >> i;
  for (auto &i : b) tifa_libs::fin_uint >> i;
  tifa_libs::fout << tifa_libs::math::conv_xor(a, b) << '\n';
  return 0;
}
