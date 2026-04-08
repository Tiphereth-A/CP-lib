#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/str/hash/lcpf/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/md/lib.hpp"
#include "../../../src/str/hash/substr2/lib.hpp"

using namespace tifa_libs;
using mint = mint_md<__LINE__>;
using namespace tifa_libs;
using mint0 = mint_md<__LINE__>;
using mint1 = mint_md<__LINE__>;
using hashstr = hash_substr2<mint0, mint1>;

int main() {
  mint::set_mod(MOD);
  mint0::set_mod(998244353);
  mint1::set_mod(1000000007);
  strn s;
  tifa_libs::fin_uint >> s;
  hashstr hs;
  hs.set(s);
  flt_ (u32, i, 0, (u32)s.size()) tifa_libs::fout << tifa_libs::lcpf_hash(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
