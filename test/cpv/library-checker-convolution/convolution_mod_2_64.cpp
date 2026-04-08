// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_2_64"

#include "../../../src/conv/add/u64/lib.hpp"
#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 n, m;
  fin_uint >> n >> m;
  vecuu a(n), b(m);
  fin_uint >> a >> b;
  fout << conv_u64(a, b) << '\n';
  return 0;
}
