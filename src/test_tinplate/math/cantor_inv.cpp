#define PROBLEM "https://vjudge.net/problem/UVA-11525"

#include "../../code/math/cantor_inv.hpp"

void solve() {
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u32> a(n);
  for (auto& i : a) std::cin >> i;
  auto p = tifa_libs::math::cantor_inv_seq(a);
  for (size_t i = 0; i < n; ++i) std::cout << p[i] << " \n"[i == n - 1];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}