#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/conv/conv_u128.hpp"
#include "../../code/util/fastio.hpp"

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<u64> a(n), b(m);
  tifa_libs::fin >> a >> b;
  auto c = tifa_libs::math::conv_u128(a, b);
  for (usz i = 0; i < c.size(); ++i) tifa_libs::fout << (u32)(c[i] % 1000000007) << " \n"[i + 1 == c.size()];
  return 0;
}
