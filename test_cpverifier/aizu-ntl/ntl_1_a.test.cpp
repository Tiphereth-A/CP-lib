#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_A"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/nt/pfactors.hpp"

int main() {
  u64 n;
  tifa_libs::fin >> n;
  auto ans = tifa_libs::math::pfactors<false>(n);
  tifa_libs::fout << n << ":";
  for (auto k : ans) tifa_libs::fout << ' ' << k;
  tifa_libs::fout << '\n';
  return 0;
}
