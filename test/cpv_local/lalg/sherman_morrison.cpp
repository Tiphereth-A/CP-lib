// competitive-verifier: STANDALONE

#include "../../../src/lalg/ds/mat/lib.hpp"
#include "../../../src/lalg/mat/ge/lib.hpp"
#include "../../../src/lalg/mat/inv/lib.hpp"
#include "../../../src/lalg/mat/sherman_morrison/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/be61n1/lib.hpp"
#include "../../../src/math/mint/md/lib.hpp"
#include "../../../src/math/mint/md64/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"
#include "../../../src/math/mint/ms64/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
template <class mint>
void single_test(u32 n) {
  rand::gen<u32> gen(1, std::numeric_limits<u32>::max());
  using mat = math::matrix<mint>;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat& m, bool f) { return math::ge_mat(m, is_0, f); };

  mat L(n, n), U(n, n);
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, i + 1) L(i, j) = gen();
  flt_ (u32, i, 0, n)
    flt_ (u32, j, i, n) U(i, j) = gen();

  mat I(n, n);
  flt_ (u32, i, 0, n) I(i, i) = 1;

  mat A = L * U;
  mat inv_A = math::inv_mat(A, is_0, ge).value();
  check(A * inv_A, I, check_param(L), check_param(U), check_param(A), check_param(inv_A));
  mat B = inv_A;
  vec<mint> u(n), v = A.data().back();
  flt_ (u32, i, 0, n) u[i] = A(i, n - 1);
  timer_(math::sherman_morrison(B, u, v));
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

using mint2e61n1 = math::mint<math::mint_2e61n1>;
using mintd31 = math::mint<math::mint_md, __LINE__>;
using mintd63 = math::mint<math::mint_md64, __LINE__>;
using mints30 = math::mint<math::mint_ms, MOD>;
using mints63 = math::mint<math::mint_ms64, MOD64>;

void test(u32 n) {
  single_test<mint2e61n1>(n);
  single_test<mintd31>(n);
  single_test<mintd63>(n);
  single_test<mints30>(n);
  single_test<mints63>(n);
}

int main() {
  mintd31::set_mod(MOD);
  mintd63::set_mod(MOD64);

  timer_(test(4));
  timer_(test(10));
  timer_(test(20));
  timer_(test(30));
  timer_(test(40));
}