#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios128.hpp"

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
