#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/lalg/sherman_morrison.hpp"

#include "../../../code/lalg/ge_mat.hpp"
#include "../../../code/lalg/inv_mat.hpp"
#include "../../../code/lalg/mat.hpp"
#include "../../../code/math/mint.hpp"
#include "../../../code/math/mint_2e61n1.hpp"
#include "../../../code/math/mint_d31.hpp"
#include "../../../code/math/mint_d63.hpp"
#include "../../../code/math/mint_s30.hpp"
#include "../../../code/math/mint_s63.hpp"
#include "../../../code/rand/gen.hpp"
#include "../base.hpp"

template <class mint>
void single_test(u32 n) {
  tifa_libs::rand::Gen<u32> gen(1, std::numeric_limits<u32>::max());
  using mat = tifa_libs::math::matrix<mint>;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat& m, bool f) { return tifa_libs::math::ge_mat(m, is_0, f); };

  mat L(n, n), U(n, n);
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, i + 1) L(i, j) = gen();
  flt_ (u32, i, 0, n)
    flt_ (u32, j, i, n) U(i, j) = gen();

  mat I(n, n);
  flt_ (u32, i, 0, n) I(i, i) = 1;

  mat A = L * U;
  mat inv_A = tifa_libs::math::inv_mat(A, is_0, ge).value();
  check(A * inv_A, I, check_param(L), check_param(U), check_param(A), check_param(inv_A));
  mat B = inv_A;
  vec<mint> u(n), v = A.data().back();
  flt_ (u32, i, 0, n) u[i] = A(i, n - 1);
  tifa_libs::math::sherman_morrison(B, u, v);
  mat A2 = A + A.submat(0, n, n - 1, n) * A.submat(n - 1, n, 0, n);
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n) {
      mint want = A(i, j) + u[i] * v[j];
      check(A2(i, j), want, check_param(A), check_param(u), check_param(v), check_param(A2));
    }
  check(B * A2, I, check_param(A), check_param(A2), check_param(B));
}

CEXP u32 MOD = 998244353;
CEXP u64 MOD64 = 3'799'912'185'593'857;

using mint2e61n1 = tifa_libs::math::mint<tifa_libs::math::mint_2e61n1>;
using mintd31 = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;
using mintd63 = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;
using mints30 = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;
using mints63 = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD64>;

void test(u32 n) {
  single_test<mint2e61n1>(n);
  single_test<mintd31>(n);
  single_test<mintd63>(n);
  single_test<mints30>(n);
  single_test<mints63>(n);
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  mintd31::set_mod(MOD);
  mintd63::set_mod(MOD64);

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