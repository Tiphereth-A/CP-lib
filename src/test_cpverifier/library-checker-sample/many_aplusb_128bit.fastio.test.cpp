#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios128.hpp"

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
