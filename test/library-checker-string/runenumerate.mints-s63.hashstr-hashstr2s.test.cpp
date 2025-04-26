#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate/"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/str/run_hash.hpp"

CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"
#include "../../include/str/hash_substr2.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using mint0 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 998244353>;
using mint1 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 1000000007>;
using hashstr = tifa_libs::str::hash_substr2<mint0, mint1>;

int main() {
  strn s;
  tifa_libs::fin >> s;
  auto res = tifa_libs::str::run_hash<hashstr>(s);
  tifa_libs::fout << res.size() << '\n';
  for (auto& [a, b, c] : res) tifa_libs::fout << a << ' ' << b << ' ' << c << '\n';
  return 0;
}