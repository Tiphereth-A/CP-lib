#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/io/fastio.hpp"
#include "../../code/str/lcpf_hash.hpp"
//
#define GENTCs_hashstrs
#define GENTCs_hashstrd0

int main() {
#define GENTCs_hashstrd1
  strn s;
  tifa_libs::fin >> s;
  hashstr hs;
  hs.set(s);
  for (u32 i = 0; i < s.size(); ++i) tifa_libs::fout << tifa_libs::str::lcpf_hash(hs, hs, 0, i) << " \n"[i + 1 == s.size()];
  return 0;
}
