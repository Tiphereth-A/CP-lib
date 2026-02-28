// competitive-verifier: STANDALONE

#include "../../../src/lalg/ds/mat/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/md/lib.hpp"
#include "../../../src/math/qpow/basic/lib.hpp"
#include "../../../src/nt/period_fib/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
template <class mint>
void test(u32 n) {
  mint::set_mod(n);
  timer_(u64 period = math::period_fib(n));
  math::matrix<mint> a(2, 2), b(2, 1), i(2, 2);
  a(0, 1) = a(1, 0) = a(1, 1) = 1;
  b(1, 0) = 1;
  i(0, 0) = i(1, 1) = 1;
  a = math::qpow(a, period, i);
  check(a * b, b, check_param(n), check_param(period), check_param(a));
}

using mint = math::mint<math::mint_md, __LINE__>;

int main() {
  timer_(test<mint>(2));
  timer_(test<mint>(10));
  timer_(test<mint>(5000));
  timer_(test<mint>(1919810));
  timer_(test<mint>(1'000'000'000));
}