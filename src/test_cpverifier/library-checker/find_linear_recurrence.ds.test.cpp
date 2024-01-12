#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "../../code/math/berlekamp_massey.hpp"
#include "../../code/math/mdata_ds.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/util/ios_container.hpp"

using mdata = tifa_libs::math::mdata_ds<-1>;
using mint = tifa_libs::math::mint<mdata>;

int main() {
  mdata::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> a(n);
  std::cin >> a;
  auto b = tifa_libs::math::berlekamp_massey(a);
  std::cout << b.size() - 1 << '\n';
  for (u32 i = 1; i < b.size(); ++i) std::cout << -b[i] << " \n"[i + 1 == b.size()];
  return 0;
}
