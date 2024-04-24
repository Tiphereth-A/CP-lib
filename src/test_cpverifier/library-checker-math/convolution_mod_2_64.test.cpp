#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_2_64"

#include "../../code/conv/karatsuba.hpp"
#include "../../code/io/fastio.hpp"

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vecu64 a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << tifa_libs::math::karatsuba(a, b) << '\n';
  return 0;
}
