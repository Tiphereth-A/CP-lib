#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"

#include "../../code/lalg/mat.hpp"
#include "../../code/lalg/mat_hafnian.hpp"
#include "../../code/math/mint_d63.hpp"
#include "../../code/util/fastio.hpp"

using mint = tifa_libs::math::mint_d63<-1>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(998244353);
  u32 n;
  tifa_libs::fin >> n;
  mat a(n, n);
  for (auto& i : a.data()) tifa_libs::fin >> i;
  tifa_libs::fout << tifa_libs::math::hafnian(a);
  return 0;
}
