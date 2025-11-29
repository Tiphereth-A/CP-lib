#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/math/josephus.hpp"

#include "../base.hpp"

using namespace tifa_libs;
decltype(unittest::default_timer.passed()) cnt_ys, cnt_bf;
vecuu Josephus_bf(u64 n, u64 k, u64 m) {
  assert(m && k && m <= n);
  assert(m <= 10000);
  vecuu ans(m);
  std::list<u64> l;
  flt_ (u64, i, 0, n) l.push_back(i);
  auto it = begin(l);
  flt_ (u32, i, 0, m) {
    flt_ (u32, j, 1, k)
      if (++it == end(l)) it = begin(l);
    ans[i] = *it;
    if ((it = l.erase(it)) == end(l)) it = begin(l);
  }
  return ans;
}

void test(u64 n, u64 k) {
  u64 m = std::min(10000_u64, n);
  unittest::default_timer.tic(__LINE__);
  auto wants = Josephus_bf(n, k, m);
  unittest::default_timer.tac();
  cnt_bf += unittest::default_timer.passed();
  flt_ (u32, i, 1, m + 1) {
    unittest::default_timer.tic(__LINE__);
    u64 got = math::Josephus(n, k, i);
    unittest::default_timer.tac();
    cnt_ys += unittest::default_timer.passed();
    check(got, wants[i - 1], check_param(n), check_param(k), check_param(i));
  }
  std::cerr << std::format("Josephus: {}, BF: {}\n", cnt_ys, cnt_bf);
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test(10, 1); break;
    case unittest::TC::example_01: test(10, 2); break;
    case unittest::TC::random_00: test(10, 3); break;
    case unittest::TC::random_01: test(1000, 1); break;
    case unittest::TC::random_02: test(1000, 2); break;
    case unittest::TC::random_03: test(1000, 3); break;
    case unittest::TC::random_04: test(1000, 42); break;
    case unittest::TC::random_05: test(1919810, 1); break;
    case unittest::TC::random_06: test(1919810, 2); break;
    case unittest::TC::random_07: test(1919810, 42); break;
    case unittest::TC::random_08: test(1919810, 114514); break;
    case unittest::TC::random_09: test(114514, 1919810); break;
    default: break;
  }

  unittest::post_test();
}