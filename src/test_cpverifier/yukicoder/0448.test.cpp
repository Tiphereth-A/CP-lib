#define PROBLEM "https://yukicoder.me/problems/448"

#include "../../code/nt/crt_mod.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  veci r(n);
  vecu m(n);
  flt_ (u32, i, 0, n) std::cin >> r[i] >> m[i];
  auto res = tifa_libs::math::crt_mod(r, m, 1'000'000'007);
  if (!res) {
    std::cout << "-1\n";
    return 0;
  }
  std::cout << ((usz)std::ranges::count(r, 0) == n ? res->second : res->first) << '\n';
  return 0;
}
