#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/lalg/sherman_morrison.hpp"

#include "../../../code/lalg/mat.hpp"
#include "../../../code/lalg/mat_ge_basic.hpp"
#include "../../../code/lalg/mat_inv.hpp"
#include "../../../code/math/mint_2e61n1.hpp"
#include "../../../code/math/mint_d31.hpp"
#include "../../../code/math/mint_d63.hpp"
#include "../../../code/math/mint_ds.hpp"
#include "../../../code/math/mint_s30.hpp"
#include "../../../code/math/mint_s63.hpp"
#include "../../../code/math/mint_ss.hpp"
#include "../../../code/rand/gen.hpp"
#include "../base.hpp"

template <class mint>
void single_test(u32 n) {
  tifa_libs::rand::Gen<std::uniform_int_distribution<u32>> gen(1, std::numeric_limits<u32>::max());
  using mat = tifa_libs::math::matrix<mint>;
  auto is_0 = [](mint const& x) { return x.val() == 0; };
  auto ge = [&is_0](mat& m, bool f) { return tifa_libs::math::ge_basic(m, is_0, f); };

  mat L(n, n), U(n, n);
  for (u32 i = 0; i < n; ++i)
    for (u32 j = 0; j <= i; ++j) L(i, j) = gen();
  for (u32 i = 0; i < n; ++i)
    for (u32 j = i; j < n; ++j) U(i, j) = gen();

  mat I(n, n);
  for (u32 i = 0; i < n; ++i) I(i, i) = 1;

  mat A = L * U;
  mat inv_A = tifa_libs::math::mat_inv(A, is_0, ge).value();
  check(A * inv_A, I, check_param(L), check_param(U), check_param(A), check_param(inv_A));
  mat B = inv_A;
  vec<mint> u(n), v = A.data().back();
  for (u32 i = 0; i < n; ++i) u[i] = A(i, n - 1);
  tifa_libs::math::sherman_morrison(B, u, v);
  mat A2 = A + A.submat(0, n, n - 1, n) * A.submat(n - 1, n, 0, n);
  for (u32 i = 0; i < n; ++i)
    for (u32 j = 0; j < n; ++j) {
      mint want = A(i, j) + u[i] * v[j];
      check(A2(i, j), want, check_param(A), check_param(u), check_param(v), check_param(A2));
    }
  check(B * A2, I, check_param(A), check_param(A2), check_param(B));
}

constexpr u32 MOD = 998244353;
constexpr u64 MOD64 = 3'799'912'185'593'857;

using mintd31 = tifa_libs::math::mint_d31<-1>;
using mintd63 = tifa_libs::math::mint_d63<-1>;
using mintds = tifa_libs::math::mint_ds<-1>;
using mints30 = tifa_libs::math::mint_s30<MOD>;
using mints63 = tifa_libs::math::mint_s63<MOD64>;
using mintss = tifa_libs::math::mint_ss<MOD>;

void test(u32 n) {
  single_test<tifa_libs::math::mint_2e61n1>(n);
  single_test<mintd31>(n);
  single_test<mintd63>(n);
  single_test<mintds>(n);
  single_test<mints30>(n);
  single_test<mints63>(n);
  single_test<mintss>(n);
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  mintd31::set_mod(MOD);
  mintd63::set_mod(MOD64);
  mintds::set_mod(MOD);

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test(4); break;
    case tifa_libs::unittest::ts_example_01: test(10); break;
    case tifa_libs::unittest::ts_random_00: test(20); break;
    case tifa_libs::unittest::ts_random_01: test(30); break;
    case tifa_libs::unittest::ts_random_02: test(40); break;
    case tifa_libs::unittest::ts_random_03: break;
    case tifa_libs::unittest::ts_random_04: break;
    case tifa_libs::unittest::ts_random_05: break;
    case tifa_libs::unittest::ts_random_06: break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}