#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/math/sum_ik_flist.hpp"

#include "../../../include/math/mpi.hpp"
#include "../../../include/math/qpow.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using math::mpi;

void test_sum_ik_flist(u64 n) {
  auto sumik_mpi = [](u64 k, u64 n) {
    mpi ret = 0;
    flt_ (u64, i, 1, n + 1) ret += qpow(mpi(i), k);
    return ret;
  };

  u64 k = 0;
  for (auto f : math::sum_ik<mpi>) {
    check(f(n), sumik_mpi(k, n), check_param(k), check_param(n));
    ++k;
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00:
      flt_ (u64, i, 0, 10) test_sum_ik_flist(i);
      break;
    case unittest::TC::example_01: test_sum_ik_flist(42); break;
    case unittest::TC::random_00: test_sum_ik_flist(114514); break;
    case unittest::TC::random_01: break;
    case unittest::TC::random_02: break;
    case unittest::TC::random_03: break;
    case unittest::TC::random_04: break;
    case unittest::TC::random_05: break;
    case unittest::TC::random_06: break;
    case unittest::TC::random_07: break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}