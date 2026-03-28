#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/conv/add/czt/lib.hpp"
#include "../../../src/fps/ds/ntt/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms<MOD>;
using namespace tifa_libs;
using poly = polyntt<mint>;
using namespace tifa_libs;
using vec_t = poly;
auto conv_func(vec_t CR a, vec_t CR b) {
  return conv_czt(a, b);
}

int main() {
  u32 n, m;
  tifa_libs::fin_uint >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin_uint >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
