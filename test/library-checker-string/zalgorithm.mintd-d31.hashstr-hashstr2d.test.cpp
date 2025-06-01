#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/str/lcpf_hash.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d31.hpp"
#include "../../include/str/hash_substr2.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_d31, __LINE__>;
using namespace tifa_libs;
using mint0 = math::mint<math::mint_d31, __LINE__>;
using mint1 = math::mint<math::mint_d31, __LINE__>;
using hashstr = str::hash_substr2<mint0, mint1>;

int main() {
  mint::set_mod(MOD);
  mint0::set_mod(998244353);
  mint1::set_mod(1000000007);
  strn s;
  tifa_libs::fin >> s;
  hashstr hs;
  hs.set(s);
  flt_ (u32, i, 0, (u32)s.size()) tifa_libs::fout << tifa_libs::str::lcpf_hash(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
