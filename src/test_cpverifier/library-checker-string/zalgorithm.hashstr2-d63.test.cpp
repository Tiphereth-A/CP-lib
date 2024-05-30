#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/io/fastio.hpp"
#include "../../code/str/lcpf_hash.hpp"
//
CEXP u32 MOD0 = 998244353;
CEXP u32 MOD1 = 1000000007;

#include "../../code/math/mint_d63.hpp"
#include "../../code/str/hash_substr2.hpp"

using mint0 = tifa_libs::math::mint_d63<-1>;
using mint1 = tifa_libs::math::mint_d63<-2>;
using hashstr = tifa_libs::str::hash_substr2<mint0, mint1>;

int main() {
  mint0::set_mod(MOD0);
  mint1::set_mod(MOD1);
  strn s;
  tifa_libs::fin >> s;
  hashstr hs;
  hs.set(s);
  flt_ (u32, i, 0, (u32)s.size()) tifa_libs::fout << tifa_libs::str::lcpf_hash(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
