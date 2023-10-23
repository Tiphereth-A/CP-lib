#define PROBLEM "https://yukicoder.me/problems/448"

#include "../../code/math/crt_mod.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n;
  std::cin >> n;
  vec<i32> r(n);
  vec<u32> m(n);
  for (size_t i = 0; i < n; ++i) std::cin >> r[i] >> m[i];
  auto res = tifa_libs::math::crt_mod(r, m, 1'000'000'007);
  if (!res) {
    std::cout << "-1\n";
    return 0;
  }
  std::cout << ((size_t)std::count(r.begin(), r.end(), 0) == n ? res->second : res->first) << '\n';
  return 0;
}
