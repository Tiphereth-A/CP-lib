#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios128.hpp"

using namespace tifa_libs;
int main() {
  u32 t;
  fin >> t;
  while (t--) {
    i128 a, b;
    fin >> a >> b;
    fout << a + b << '\n';
  }
  return 0;
}
