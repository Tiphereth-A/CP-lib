#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/str/z_func.hpp"

int main() {
  strn s;
  tifa_libs::fin >> s;
  tifa_libs::fout << tifa_libs::str::z_func(s) << '\n';
  return 0;
}
