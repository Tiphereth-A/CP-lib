#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_d31.hpp"
#include "../../code/str/hash_substr2.hpp"
#include "../../code/str/lcp_hashstr.hpp"
#include "../../code/util/fastio.hpp"

using mintdata0 = tifa_libs::math::mintdata_d31<-1>;
using mintdata1 = tifa_libs::math::mintdata_d31<-2>;
using mint0 = tifa_libs::math::mint<mintdata0>;
using mint1 = tifa_libs::math::mint<mintdata1>;
using hashstr = tifa_libs::str::hash_substr2<mint0, mint1>;

int main() {
  mintdata0::set_mod(998244353);
  mintdata1::set_mod(1'000'000'007);
  strn s;
  tifa_libs::fin >> s;
  hashstr hs;
  hs.set(s);
  for (u32 i = 0; i < s.size(); ++i) tifa_libs::fout << tifa_libs::str::lcp_hashstr(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
