#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"

#include "../../code/io/ios_container.hpp"
#include "../../code/math/do_quot.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  vecu64 ans;
  tifa_libs::math::do_quot(n, [&ans](u64, u64, u64 q) { ans.push_back(q); });
  std::ranges::sort(ans);
  std::cout << ans.size() << '\n';
  std::cout << ans << '\n';
  return 0;
}
