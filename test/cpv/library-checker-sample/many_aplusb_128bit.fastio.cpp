// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/many_aplusb_128bit
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/io/i128/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 t;
  fin_uint >> t;
  while (t--) {
    i128 a, b;
    fin_int >> a >> b;
    fout << a + b << '\n';
  }
  return 0;
}
