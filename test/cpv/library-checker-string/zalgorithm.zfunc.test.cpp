#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/str/z_func/lib.hpp"

using namespace tifa_libs;
int main() {
  strn s;
  fin >> s;
  fout << str::z_func(s) << '\n';
  return 0;
}
