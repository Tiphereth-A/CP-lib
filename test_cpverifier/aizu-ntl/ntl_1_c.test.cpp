#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_C"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/nt/lcm.hpp"
#include "../../include/nt/rgcd.hpp"

CEXP u32 LIMIT = 1e7;

int main() {
  u64 n;
  u32 ans;
  tifa_libs::fin >> n >> ans;
  tifa_libs::math::rgcd rgcd_(LIMIT);
  for (u32 i = 1, x; i < n; ++i) {
    tifa_libs::fin >> x;
    if (ans < LIMIT) (ans /= rgcd_(ans, x)) *= x;
    else ans = tifa_libs::math::lcm(ans, x);
  }
  tifa_libs::fout << ans << '\n';
  return 0;
}
