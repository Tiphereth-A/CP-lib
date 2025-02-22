#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_big_integers"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/math/mpi.hpp"

int main() {
  u32 t;
  tifa_libs::fin >> t;
  while (t--) {
    tifa_libs::math::mpi a, b;
    tifa_libs::fin >> a >> b;
    tifa_libs::fout << a * b << '\n';
  }
  return 0;
}
