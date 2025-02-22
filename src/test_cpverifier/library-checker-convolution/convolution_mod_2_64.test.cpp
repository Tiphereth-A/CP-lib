#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_2_64"

#include "../../code/conv/conv_u64.hpp"
#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios_container.hpp"

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vecuu a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << tifa_libs::math::conv_u64(a, b) << '\n';
  return 0;
}
