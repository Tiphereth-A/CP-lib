#define PROBLEM "https://www.luogu.com.cn/problem/P5367"

#include "../../code/math/cantor.hpp"

void solve() {
  u32 n;
  std::cin >> n;
  vec<u32> a(n);
  for (auto& i : a) std::cin >> i;
  std::cout << tifa_libs::math::cantor_val(a, 998244353) << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}