#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/runenumerate/"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/str/run/hash/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/bd/lib.hpp"
#include "../../../src/str/hash/substr2/lib.hpp"

using namespace tifa_libs;
using mint = mint_bd<__LINE__>;
using namespace tifa_libs;
using mint0 = mint_bd<__LINE__>;
using mint1 = mint_bd<__LINE__>;
using hashstr = hash_substr2<mint0, mint1>;

int main() {
  mint::set_mod(MOD);
  mint0::set_mod(998244353);
  mint1::set_mod(1000000007);
  strn s;
  tifa_libs::fin_uint >> s;
  auto res = tifa_libs::run_hash<hashstr>(s);
  tifa_libs::fout << res.size() << '\n';
  for (auto& [a, b, c] : res) tifa_libs::fout << a << ' ' << b << ' ' << c << '\n';
  return 0;
}