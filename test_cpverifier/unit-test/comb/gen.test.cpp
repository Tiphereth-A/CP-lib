#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/comb/gen_fact.hpp"
#include "../../../include/comb/gen_ifact.hpp"
#include "../../../include/comb/gen_inv.hpp"
#include "../../../include/comb/gen_invseq.hpp"
#include "../../../include/comb/gen_ipowi.hpp"
#include "../../../include/comb/gen_pows.hpp"
#include "../../../include/math/mint.hpp"
#include "../../../include/math/mint_d31.hpp"
#include "../../../include/math/mint_d63.hpp"
#include "../../../include/math/mint_s30.hpp"
#include "../../../include/math/mint_s63.hpp"
#include "../../../include/math/qpow.hpp"
#include "../base.hpp"

tifa_libs::rand::Gen<u64> g(1);

template <class mint>
void test_all(u32 n) {
  [](u32 n) {  // fact & ifact
    auto fact = tifa_libs::math::gen_fact<mint>(n);
    auto ifact = tifa_libs::math::gen_ifact<mint>(n);
    mint bf = 1;
    flt_ (u32, i, 0, n) {
      if (i) bf *= i;
      check(fact[i], bf, check_param(i));
      check(ifact[i], bf.inv(), check_param(i));
    }
  }(n);
  [](u32 n) {  // inv
    auto inv = tifa_libs::math::gen_inv<mint>(n);
    flt_ (u32, i, 1, n) {
      auto bf = mint{i}.inv();
      check(inv[i], bf, check_param(i));
    }
  }(n);
  [](u32 n) {  // invseq
    vec<mint> seq;
    std::generate_n(std::back_inserter(seq), n, [&] { return mint(g()); });
    auto invseq = tifa_libs::math::gen_invseq(seq);
    flt_ (u32, i, 0, n) {
      auto bf = seq[i].inv();
      check(invseq[i], bf, check_param(i), check_param(seq[i]));
    }
  }(n);
  [](u32 n) {  // ipowi
    auto ipowi = tifa_libs::math::gen_ipowi<mint>(n);
    flt_ (u32, i, 0, n) {
      auto bf = tifa_libs::math::qpow<mint>(i, i);
      check(ipowi[i], bf, check_param(i));
    }
  }(n);
  auto test_pows = [](u32 n, u32 b) {  // pows
    auto pows = tifa_libs::math::gen_pows<mint>(n, b);
    flt_ (u32, i, 0, n) {
      auto bf = tifa_libs::math::qpow<mint>(i, b);
      check(pows[i], bf, check_param(i), check_param(b));
    }
  };
  test_pows(n, 0);
  test_pows(n, 1);
  test_pows(n, 114514);
  test_pows(n, n);
}

using mints30 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 998244353>;
using mints63 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 998244353>;
using mintd31 = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;
using mintd63 = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;

int main() {
  auto tcase = tifa_libs::unittest::pre_test();
  mintd31::set_mod(1000000000 + 7);
  mintd63::set_mod(1000000000 + 7);

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test_all<mints30>(1000); break;
    case tifa_libs::unittest::ts_example_01: test_all<mints63>(1000); break;
    case tifa_libs::unittest::ts_random_00: test_all<mintd31>(1000); break;
    case tifa_libs::unittest::ts_random_01: test_all<mintd63>(1000); break;
    case tifa_libs::unittest::ts_random_02: test_all<mints30>(1'000'000); break;
    case tifa_libs::unittest::ts_random_03: test_all<mints63>(1'000'000); break;
    case tifa_libs::unittest::ts_random_04: test_all<mintd31>(1'000'000); break;
    case tifa_libs::unittest::ts_random_05: test_all<mintd63>(1'000'000); break;
    case tifa_libs::unittest::ts_random_06: break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}