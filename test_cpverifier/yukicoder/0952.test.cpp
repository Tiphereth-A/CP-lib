#define PROBLEM "https://yukicoder.me/problems/no/952"

#include "../../include/opt/larsch_2d.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecii a(n), b(n + 1);
  for (auto& i : a) std::cin >> i;
  std::inclusive_scan(a.begin(), a.end(), b.begin() + 1);
  auto w = [&](u32 i, u32 j) -> i64 { return i + 1 == j ? 0 : (b[j - 1] - b[i]) * (b[j - 1] - b[i]); };
  auto ans = tifa_libs::opt::larsch_2d<i64>(n + 1, w);
  for (u32 i = n; i; --i) std::cout << ans[i] << '\n';
  return 0;
}
