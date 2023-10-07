// https://www.luogu.com.cn/problem/P5367

#include "../../code/math/cantor.hpp"

void solve() {
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u32> a(n);
  for (auto& i : a) std::cin >> i;
  std::cout << tifa_libs::math::cantor(a, 998244353) << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}