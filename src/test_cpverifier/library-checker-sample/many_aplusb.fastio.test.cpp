#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "../../code/io/fastio.hpp"

int main() {
  u32 t;
  tifa_libs::fin >> t;
  while (t--) {
    i128 a, b;
    tifa_libs::fin >> a >> b;
    tifa_libs::fout << a + b << '\n';
  }
  return 0;
}
