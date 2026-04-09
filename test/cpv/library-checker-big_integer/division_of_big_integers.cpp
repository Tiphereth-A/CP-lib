// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/division_of_big_integers
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/io/pair/lib.hpp"
#include "../../../src/math/ds/mpi/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 t;
  fin_uint >> t;
  while (t--) {
    mpi a, b;
    fin_uint >> a >> b;
    fout << divmod(a, b) << '\n';
  }
  return 0;
}
