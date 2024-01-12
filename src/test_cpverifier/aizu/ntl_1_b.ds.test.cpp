#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"

#include "../../code/math/mdata_ds.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/qpow.hpp"

constexpr u64 MOD = 1'000'000'007;
using mdata = tifa_libs::math::mdata_ds<-1>;
using mint = tifa_libs::math::mint<mdata>;

int main() {
  mdata::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  mint m;
  u64 n;
  std::cin >> m >> n;
  std::cout << tifa_libs::math::qpow(m, n).val() << '\n';
  return 0;
}
