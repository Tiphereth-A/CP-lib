#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include "../../code/lalg/mat_charpoly.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_d63.hpp"
#include "../../code/io/ios_container.hpp"

using mintdata = tifa_libs::math::mintdata_d63<-1>;
using mint = tifa_libs::math::mint<mintdata>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mintdata::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
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
