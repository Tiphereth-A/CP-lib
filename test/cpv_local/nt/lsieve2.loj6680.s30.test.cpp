// competitive-verifier: STANDALONE

// clang-format off
#include "../../../src/util/op/pair/lib.hpp"
// clang-format on

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"
#include "../../../src/nt/lsieve/impl2/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, 998244353>;

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("loj", "6680", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n;
  fin >> n;
  math::lsieve2 ls(n);
  ptt<mint> lst;
  vecpt<mint> g = ls.run([&](u32 p, u32 e) {
    if (e == 1) return lst = ptt<mint>(p + (p ^ 1), 1 + (p ^ 1));
    else return lst = ptt<mint>((lst.first * p + (p ^ e)), (lst.second + (p ^ e)));
  },
                         ptt<mint>{1, 1});

  vec<mint> f(n + 1);
  f[1] = 1;
  flt_ (u32, i, 2, n + 1) f[i] = f[i - 1] + g[i].first + g[i].first - g[i].second;
  u64 got = f[1].val();
  flt_ (u32, i, 2, n + 1) got ^= f[i].val();

  u64 want;
  fans >> want;
  check(got, want, check_param(data));
}

int main() {
  for (int i = 1; i <= 20; ++i) {
    timer_(test(std::to_string(i)));
  }
}