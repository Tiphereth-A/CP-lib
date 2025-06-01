#define PROBLEM "https://judge.yosupo.jp/problem/division_of_big_integers"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_pair.hpp"
#include "../../include/math/mpi.hpp"

using namespace tifa_libs;
int main() {
  u32 t;
  fin >> t;
  while (t--) {
    math::mpi a, b;
    fin >> a >> b;
    fout << divmod(a, b) << '\n';
  }
  return 0;
}
