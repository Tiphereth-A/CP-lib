#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_2_64"

#include "../../include/conv/conv_u64.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
int main() {
  u32 n, m;
  fin >> n >> m;
  vecuu a(n), b(m);
  fin >> a >> b;
  fout << math::conv_u64(a, b) << '\n';
  return 0;
}
