#define PROBLEM "https://yukicoder.me/problems/448"

#include "../../code/nt/crt_mod.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<i32> r(n);
  vecu m(n);
  for (u32 i = 0; i < n; ++i) std::cin >> r[i] >> m[i];
  auto res = tifa_libs::math::crt_mod(r, m, 1'000'000'007);
  if (!res) {
    std::cout << "-1\n";
    return 0;
  }
  std::cout << ((usz)std::count(r.begin(), r.end(), 0) == n ? res->second : res->first) << '\n';
  return 0;
}
