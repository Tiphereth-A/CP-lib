// competitive-verifier: STANDALONE

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"
#include "../../../src/math/qpow/basic/lib.hpp"
#include "../../../src/nt/lsieve/impl2/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, 1'000'000'000 + 7>;

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("loj", "124", "sieve"s + data.data());
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n, k;
  fin >> n >> k;
  math::lsieve2 ls(n);
  mint pk = 1, lst = 1;
  vec<mint> dk = ls.template run<mint>([&](u32 p, u32 e) {
    if (e == 1) pk = math::qpow<mint>(p, k), lst = 1 + pk;
    else lst = lst * pk + 1;
    return lst;
  });
  mint res = 0;
  flt_ (u32, i, 1, n + 1) res += dk[i];

  u64 got = res.val(), want;
  fans >> want;
  check(got, want, check_param(data));
}

int main() {
  for (int i = 0; i <= 24; ++i) {
    timer_(test(std::to_string(i)));
  }
}