#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include "../../code/io/ios_container.hpp"
#include "../../code/lalg/mat_charpoly.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ss.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  if (n == 0) {
    std::cout << "1\n";
    return 0;
  }
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x.val() == 0; };
  std::cout << tifa_libs::math::charpoly(a, is_0) << '\n';
  return 0;
}
