#define AUTO_GENERATED
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/runenumerate/
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/str/run/hash/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/be61n1/lib.hpp"
#include "../../../src/str/hash/substr/lib.hpp"

using namespace tifa_libs;
using mint = mint_2e61n1;
using hashstr = hash_substr<mint>;

int main() {
  strn s;
  tifa_libs::fin_uint >> s;
  auto res = tifa_libs::run_hash<hashstr>(s);
  tifa_libs::fout << res.size() << '\n';
  for (auto& [a, b, c] : res) tifa_libs::fout << a << ' ' << b << ' ' << c << '\n';
  return 0;
}