#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/math/mdata_ds.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/str/hash_substr2.hpp"
#include "../../code/str/lcp_hashstr.hpp"
#include "../../code/util/fastio.hpp"

using mdata0 = tifa_libs::math::mdata_ds<-1>;
using mdata1 = tifa_libs::math::mdata_ds<-2>;
using mint0 = tifa_libs::math::mint<mdata0>;
using mint1 = tifa_libs::math::mint<mdata1>;
using hashstr = tifa_libs::str::hash_substr2<mint0, mint1>;

int main() {
  mdata0::set_mod(998244353);
  mdata1::set_mod(1'000'000'007);
  std::string s;
  tifa_libs::fin >> s;
  hashstr hs;
  hs.set(s);
  for (u32 i = 0; i < s.size(); ++i) tifa_libs::fout << tifa_libs::str::lcp_hashstr(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
