#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/math/sum_ik_flist.hpp"

#include "../../../code/math/mpi.hpp"
#include "../../../code/math/qpow.hpp"
#include "../base.hpp"

using u64;
using tifa_libs::math::mpi;

void test_sum_ik_flist(u64 n) {
  auto sumik_mpi = [](u64 k, u64 n) {
    mpi ret = 0;
    for (u64 i = 1; i <= n; ++i) ret += qpow(mpi(i), k);
    return ret;
  };

  u64 k = 0;
  for (auto f : tifa_libs::math::sum_ik<mpi>) {
    check(f(n), sumik_mpi(k, n), check_param(k), check_param(n));
    ++k;
  }
}

int main() {
  tifa_libs::unittest::pre_test();

  for (u64 i = 0; i < 10; ++i) test_sum_ik_flist(i);
  test_sum_ik_flist(42);
  test_sum_ik_flist(114514);

  tifa_libs::unittest::post_test();
}