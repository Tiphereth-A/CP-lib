#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_A"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/nt/pfactors.hpp"

int main() {
  u64 n;
  tifa_libs::fin >> n;
  auto ans = tifa_libs::math::pfactors<false>(n);
  tifa_libs::fout << n << ":";
  for (auto k : ans) tifa_libs::fout << ' ' << k;
  tifa_libs::fout << '\n';
  return 0;
}
