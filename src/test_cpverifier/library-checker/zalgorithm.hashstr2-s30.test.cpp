#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/io/fastio.hpp"
#include "../../code/str/lcp_hashstr.hpp"

constexpr u32 MOD0 = 998244353;
constexpr u32 MOD1 = 1000000007;

#include "../../code/math/mint_s30.hpp"
#include "../../code/str/hash_substr2.hpp"

using mint0 = tifa_libs::math::mint_s30<MOD0>;
using mint1 = tifa_libs::math::mint_s30<MOD1>;
using hashstr = tifa_libs::str::hash_substr2<mint0, mint1>;

int main() {
  strn s;
  tifa_libs::fin >> s;
  hashstr hs;
  hs.set(s);
  for (u32 i = 0; i < s.size(); ++i) tifa_libs::fout << tifa_libs::str::lcp_hashstr(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
