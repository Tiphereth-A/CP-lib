#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_A"

#include "../../code/io/fastio.hpp"
#include "../../code/nt/pfactors.hpp"

int main() {
  u64 n;
  tifa_libs::fin >> n;
  auto ans = tifa_libs::math::pfactors(n);
  tifa_libs::fout << n << ":";
  for (auto [k, v] : ans)
    for (u32 i = 0; i < v; ++i) tifa_libs::fout << ' ' << k;
  tifa_libs::fout << '\n';
  return 0;
}
