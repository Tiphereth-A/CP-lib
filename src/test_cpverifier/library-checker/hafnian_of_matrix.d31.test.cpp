#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"

#include "../../code/lalg/mat.hpp"
#include "../../code/lalg/mat_hafnian.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_d31.hpp"

using mintdata = tifa_libs::math::mintdata_d31<-1>;
using mint = tifa_libs::math::mint<mintdata>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mintdata::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  std::cout << tifa_libs::math::hafnian(a);
  return 0;
}
