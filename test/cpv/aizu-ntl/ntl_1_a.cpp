#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_A"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/nt/pfactors/lib.hpp"

using namespace tifa_libs;
int main() {
  u64 n;
  fin_uint >> n;
  auto ans = pfactors<false>(n);
  fout << n << ":";
  for (auto k : ans) fout << ' ' << k;
  fout << '\n';
  return 0;
}
