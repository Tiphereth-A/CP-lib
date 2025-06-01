#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_A"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/nt/pfactors.hpp"

using namespace tifa_libs;
int main() {
  u64 n;
  fin >> n;
  auto ans = math::pfactors<false>(n);
  fout << n << ":";
  for (auto k : ans) fout << ' ' << k;
  fout << '\n';
  return 0;
}
