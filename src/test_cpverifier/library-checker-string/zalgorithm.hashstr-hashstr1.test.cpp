#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/str/lcpf_hash.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_2e61n1.hpp"
#include "../../code/str/hash_substr.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_2e61n1>;
using hashstr = tifa_libs::str::hash_substr<mint>;

int main() {
  strn s;
  tifa_libs::fin >> s;
  hashstr hs;
  hs.set(s);
  flt_ (u32, i, 0, (u32)s.size()) tifa_libs::fout << tifa_libs::str::lcpf_hash(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
