#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/str/hash/lcpf/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms64/lib.hpp"
#include "../../../src/str/hash/substr2/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms64, MOD>;
using namespace tifa_libs;
using mint0 = math::mint<math::mint_ms64, 998244353>;
using mint1 = math::mint<math::mint_ms64, 1000000007>;
using hashstr = str::hash_substr2<mint0, mint1>;

int main() {
  strn s;
  tifa_libs::fin_uint >> s;
  hashstr hs;
  hs.set(s);
  flt_ (u32, i, 0, (u32)s.size()) tifa_libs::fout << tifa_libs::str::lcpf_hash(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
