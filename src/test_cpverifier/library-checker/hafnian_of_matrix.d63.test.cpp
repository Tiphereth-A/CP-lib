#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"

#include "../../code/lalg/mat.hpp"
#include "../../code/lalg/mat_hafnian.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_d63.hpp"
#include "../../code/io/fastio.hpp"

using mintdata = tifa_libs::math::mintdata_d63<-1>;
using mint = tifa_libs::math::mint<mintdata>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mintdata::set_mod(998244353);
  u32 n;
  tifa_libs::fin >> n;
  mat a(n, n);
  for (auto& i : a.data()) tifa_libs::fin >> i;
  tifa_libs::fout << tifa_libs::math::hafnian(a);
  return 0;
}
