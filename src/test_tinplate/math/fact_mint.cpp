#define PROBLEM "https://www.luogu.com.cn/problem/P5282"

#include "../../code/math/fact_mint.hpp"

#include "../../code/math/mint_d31.hpp"
#include "../../code/poly/polydata_d.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using polyd = tifa_libs::math::polydata_d<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::u32 n, p;
    std::cin >> n >> p;
    mint::set_mod(p);
    std::cout << tifa_libs::math::fact_mint<polyd>(n) << '\n';
  }
  return 0;
}
