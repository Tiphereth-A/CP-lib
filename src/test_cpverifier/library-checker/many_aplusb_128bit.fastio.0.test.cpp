#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include "../../code/util/fastio.hpp"

int main() {
  tifa_libs::u32 t;
  tifa_libs::fin >> t;
  while (t--) {
    tifa_libs::i128 a, b;
    tifa_libs::fin >> a >> b;
    tifa_libs::fout << a + b << '\n';
  }
  return 0;
}
