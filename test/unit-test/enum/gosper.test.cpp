#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/enum/gosper.hpp"

#include "../../../include/comb/binom.hpp"
#include "../../../include/math/mint.hpp"
#include "../../../include/math/mint_s30.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, 998244353>;

template <u32 ID>
void test(u32 n, u32 kmax) {
  using gosper = gosper<ID>;
  math::binom<mint> binom(n);
  timer_(flt_ (u32, k, 1, kmax + 1) {
    gosper::set(n, k);
    gosper gs;
    u32 cnt = 0, cnt_correct = binom.mCn(n, k).val();
    for (auto i : gs) {
      ++cnt;
      check((u32)std::popcount(i), k, check_param(n), check_param(k), check_param(std::bitset<64>(i).to_string()));
    }
    check(cnt, cnt_correct, check_param(n), check_param(k));
  });
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test<1>(1, 1); break;
    case unittest::TC::example_01: test<1>(2, 2); break;
    case unittest::TC::random_00: test<1>(3, 3); break;
    case unittest::TC::random_01: test<1>(4, 4); break;
    case unittest::TC::random_02: test<1>(5, 5); break;
    case unittest::TC::random_03: test<1>(6, 6); break;
    case unittest::TC::random_04: test<2>(10, 10); break;
    case unittest::TC::random_05: test<2>(20, 20); break;
    case unittest::TC::random_06: test<2>(30, 10); break;
    case unittest::TC::random_07: test<2>(40, 8); break;
    case unittest::TC::random_08: test<2>(50, 7); break;
    case unittest::TC::random_09: test<2>(60, 6); break;
    default: break;
  }

  unittest::post_test();
}