// competitive-verifier: STANDALONE

#include "../../../src/math/ds/mpi/lib.hpp"
#include "../../../src/math/qpow/basic/lib.hpp"
#include "../../../src/math/sum_ik_flist/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using math::mpi;

void test(u64 n) {
  auto sumik_mpi = [](u64 k, u64 n) {
    mpi ret = 0;
    timer_(flt_ (u64, i, 1, n + 1) ret += qpow(mpi(i), k));
    return ret;
  };

  u64 k = 0;
  for (auto f : math::sum_ik<mpi>) {
    timer_(check(f(n), sumik_mpi(k, n), check_param(k), check_param(n)));
    ++k;
  }
}

int main() {
  flt_ (u64, i, 0, 10) {
    timer_(test(i));
  }
  timer_(test(42));
  timer_(test(114514));
}