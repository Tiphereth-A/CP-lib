#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_B"

#include "../../code/opt/hoverline.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 h, w;
  std::cin >> h >> w;
  vecu v(w);
  u64 ans = 0;
  flt_ (u32, i, 0, h) {
    flt_ (u32, j, 0, w, x) {
      std::cin >> x;
      if (x) v[j] = 0;
      else ++v[j];
    }
    auto [l, r] = tifa_libs::opt::hoverline(v);
    flt_ (u32, j, 0, w) ans = max(ans, (r[j] - l[j] + 1_u64) * v[j]);
  }
  std::cout << ans << '\n';
  return 0;
}
