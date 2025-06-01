#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/str/z_func.hpp"

using namespace tifa_libs;
int main() {
  strn s;
  fin >> s;
  fout << str::z_func(s) << '\n';
  return 0;
}
