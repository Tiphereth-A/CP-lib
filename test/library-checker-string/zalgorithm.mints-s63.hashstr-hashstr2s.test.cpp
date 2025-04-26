#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/str/lcpf_hash.hpp"

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
  hashstr hs;
  hs.set(s);
  flt_ (u32, i, 0, (u32)s.size()) tifa_libs::fout << tifa_libs::str::lcpf_hash(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
