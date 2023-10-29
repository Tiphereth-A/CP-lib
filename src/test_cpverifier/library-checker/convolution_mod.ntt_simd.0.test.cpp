#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/fast/ntt_simd.hpp"
#include "../../code/util/fastio.hpp"

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<u32> a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << tifa_libs::math::NTT(998244353).conv(a, b) << '\n';
  return 0;
}
