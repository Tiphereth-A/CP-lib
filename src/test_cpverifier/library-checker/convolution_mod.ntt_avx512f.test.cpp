#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/fast/ntt_avx512f.hpp"
#include "../../code/util/fastio.hpp"

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<u32> a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << tifa_libs::math::NTT_AVX512F(998244353).conv(a, b) << '\n';
  return 0;
}
