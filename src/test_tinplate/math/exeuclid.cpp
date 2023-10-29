#define PROBLEM "https://www.luogu.com.cn/problem/P5170"

#include "../../code/math/exeuclid.hpp"

#include "../../code/math/mint_ss.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using node = tifa_libs::math::exeuclid_node<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  node u(1, 0, 0, 0, 0, 0), r(0, 1, 1, 0, 0, 0);
  while (t--) {
    u64 n, a, b, c;
    std::cin >> n >> a >> b >> c;
    auto ans = tifa_libs::math::exeuclid(a, c, b, n, u, r);
    std::cout << (ans.f + b / c) << ' ' << (ans.sqr_f + (b / c) * (b / c)) << ' ' << ans.i_f << '\n';
  }
  return 0;
}
