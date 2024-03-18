#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/str/z_func.hpp"
#include "../../code/io/fastio.hpp"

int main() {
  strn s;
  tifa_libs::fin >> s;
  tifa_libs::fout << tifa_libs::str::z_func(s) << '\n';
  return 0;
}
