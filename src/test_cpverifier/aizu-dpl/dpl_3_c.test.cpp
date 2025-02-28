#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_C"

#include "../../code/io/ios_container.hpp"
#include "../../code/opt/hoverline.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu v(n);
  std::cin >> v;
  auto [l, r] = tifa_libs::opt::hoverline(v);
  u64 ans = 0;
  flt_ (u32, i, 0, n) ans = max(ans, (r[i] - l[i] + 1_u64) * v[i]);
  std::cout << ans << '\n';
  return 0;
}
