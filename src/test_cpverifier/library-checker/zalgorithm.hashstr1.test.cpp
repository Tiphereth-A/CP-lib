#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/math/mint_2e61n1.hpp"
#include "../../code/str/hash_substr.hpp"
#include "../../code/str/lcp_hashstr.hpp"
#include "../../code/util/fastio.hpp"

using mint = tifa_libs::math::mint_2e61n1;
using hashstr = tifa_libs::str::hash_substr<mint>;

int main() {
  std::string s;
  tifa_libs::fin >> s;
  hashstr hs;
  hs.set(s);
  for (u32 i = 0; i < s.size(); ++i) tifa_libs::fout << tifa_libs::str::lcp_hashstr(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
