// competitive-verifier: STANDALONE
#include "../../../src/comb/seq/fact/lib.hpp"
#include "../../../src/comb/seq/ifact/lib.hpp"
#include "../../../src/comb/seq/inv/lib.hpp"
#include "../../../src/comb/seq/invseq/lib.hpp"
#include "../../../src/comb/seq/ipowi/lib.hpp"
#include "../../../src/comb/seq/pows/lib.hpp"
#include "../../../src/math/ds/mint/md/lib.hpp"
#include "../../../src/math/ds/mint/md64/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"
#include "../../../src/math/qpow/basic/lib.hpp"
#include "../../../src/util/rand/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
rand_gen<u64> g(1);

template <class mint>
void test_all(u32 n) {
  [](u32 n) {  // fact & ifact
    timer_(auto fact = gen_fact<mint>(n));
    timer_(auto ifact = gen_ifact<mint>(n));
    mint bf = 1;
    flt_ (u32, i, 0, n) {
      if (i) bf *= i;
      check(fact[i], bf, check_param(i));
      check(ifact[i], bf.inv(), check_param(i));
    }
  }(n);
  [](u32 n) {  // inv
    timer_(auto inv = gen_inv<mint>(n));
    flt_ (u32, i, 1, n) {
      auto bf = mint{i}.inv();
      check(inv[i], bf, check_param(i));
    }
  }(n);
  [](u32 n) {  // invseq
    vec<mint> seq;
    timer_(std::generate_n(std::back_inserter(seq), n, [&] { return mint(g()); }));
    auto invseq = gen_invseq(seq);
    flt_ (u32, i, 0, n) {
      auto bf = seq[i].inv();
      check(invseq[i], bf, check_param(i), check_param(seq[i]));
    }
  }(n);
  [](u32 n) {  // ipowi
    timer_(auto ipowi = gen_ipowi<mint>(n));
    flt_ (u32, i, 0, n) {
      auto bf = qpow<mint>(i, i);
      check(ipowi[i], bf, check_param(i));
    }
  }(n);
  auto test_pows = [](u32 n, u32 b) {  // pows
    timer_(auto pows = gen_pows<mint>(n, b));
    flt_ (u32, i, 0, n) {
      auto bf = qpow<mint>(i, b);
      check(pows[i], bf, check_param(i), check_param(b));
    }
  };
  timer_(test_pows(n, 0));
  timer_(test_pows(n, 1));
  timer_(test_pows(n, 114514));
  timer_(test_pows(n, n));
}

using mints30 = mint_ms<998244353>;
using mints63 = mint_ms64<998244353>;
using mintd31 = mint_md<__LINE__>;
using mintd63 = mint_md64<__LINE__>;

int main() {
  mintd31::set_mod(1000000000 + 7);
  mintd63::set_mod(1000000000 + 7);

  timer_(test_all<mints30>(1000));
  timer_(test_all<mints63>(1000));
  timer_(test_all<mintd31>(1000));
  timer_(test_all<mintd63>(1000));
  timer_(test_all<mints30>(1'000'000));
  timer_(test_all<mints63>(1'000'000));
  timer_(test_all<mintd31>(1'000'000));
  timer_(test_all<mintd63>(1'000'000));
}