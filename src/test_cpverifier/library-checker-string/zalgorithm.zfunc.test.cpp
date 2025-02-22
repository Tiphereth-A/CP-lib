#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios_container.hpp"
#include "../../code/str/z_func.hpp"

int main() {
  strn s;
  tifa_libs::fin >> s;
  tifa_libs::fout << tifa_libs::str::z_func(s) << '\n';
  return 0;
}
