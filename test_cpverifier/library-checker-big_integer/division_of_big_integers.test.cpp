#define PROBLEM "https://judge.yosupo.jp/problem/division_of_big_integers"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_pair.hpp"
#include "../../include/math/mpi.hpp"

int main() {
  u32 t;
  tifa_libs::fin >> t;
  while (t--) {
    tifa_libs::math::mpi a, b;
    tifa_libs::fin >> a >> b;
    tifa_libs::fout << divmod(a, b) << '\n';
  }
  return 0;
}
