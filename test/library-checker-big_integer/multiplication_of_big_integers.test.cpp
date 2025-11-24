#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_big_integers"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/math/mpi.hpp"

using namespace tifa_libs;
int main() {
  u32 t;
  fin_uint >> t;
  while (t--) {
    math::mpi a, b;
    fin_uint >> a >> b;
    fout << a * b << '\n';
  }
  return 0;
}
