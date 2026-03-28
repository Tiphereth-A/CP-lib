// competitive-verifier: STANDALONE

#include "../../../src/comb/binom/lib.hpp"
#include "../../../src/gen/gosper/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using mint = mint_ms<998244353>;

template <u32 ID>
void test(u32 n, u32 kmax) {
  binom<mint> binom(n);
  timer_(flt_ (u32, k, 1, kmax + 1) {
    gosper<ID>::set(n, k);
    gosper<ID> gs;
    u32 cnt = 0, cnt_correct = binom.mCn(n, k).val();
    for (auto i : gs) {
      ++cnt;
      check((u32)std::popcount(i), k, check_param(n), check_param(k), check_param(std::bitset<64>(i).to_string()));
    }
    check(cnt, cnt_correct, check_param(n), check_param(k));
  });
}

int main() {
  timer_(test<1>(1, 1));
  timer_(test<1>(2, 2));
  timer_(test<1>(3, 3));
  timer_(test<1>(4, 4));
  timer_(test<1>(5, 5));
  timer_(test<1>(6, 6));
  timer_(test<2>(10, 10));
  timer_(test<2>(20, 20));
  timer_(test<2>(30, 10));
  timer_(test<2>(40, 8));
  timer_(test<2>(50, 7));
  timer_(test<2>(60, 6));
}