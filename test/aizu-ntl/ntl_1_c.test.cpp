#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_C"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/nt/lcm.hpp"
#include "../../include/nt/rgcd.hpp"

using namespace tifa_libs;
CEXP u32 LIMIT = 1e7;

int main() {
  u64 n;
  u32 ans;
  fin >> n >> ans;
  math::rgcd rgcd_(LIMIT);
  for (u32 i = 1, x; i < n; ++i) {
    fin >> x;
    if (ans < LIMIT) (ans /= rgcd_(ans, x)) *= x;
    else ans = math::lcm(ans, x);
  }
  fout << ans << '\n';
  return 0;
}
