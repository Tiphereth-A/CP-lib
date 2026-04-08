// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 t;
  fin_uint >> t;
  while (t--) {
    u64 a, b;
    fin_uint >> a >> b;
    fout << a + b << '\n';
  }
  return 0;
}
