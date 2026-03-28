#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_C"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/nt/gl/lcm/lib.hpp"
#include "../../../src/nt/gl/rgcd/lib.hpp"

using namespace tifa_libs;
CEXP u32 LIMIT = 1e7;

int main() {
  u64 n;
  u32 ans;
  fin_uint >> n >> ans;
  rgcd rgcd_(LIMIT);
  for (u32 i = 1, x; i < n; ++i) {
    fin_uint >> x;
    if (ans < LIMIT) (ans /= rgcd_(ans, x)) *= x;
    else ans = lcm(ans, x);
  }
  fout << ans << '\n';
  return 0;
}
