#define PROBLEM "https://judge.yosupo.jp/problem/division_of_hex_big_integers"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/math/ds/mpi/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 t;
  fin_uint >> t;
  strn s1, s2;
  while (t--) {
    fin >> s1 >> s2;
    mpi a = mpi::from_hex_str(s1), b = mpi::from_hex_str(s2);
    auto [q, r] = divmod(a, b);
    fout << q.to_hex_str() << " " << r.to_hex_str() << '\n';
  }
  return 0;
}
