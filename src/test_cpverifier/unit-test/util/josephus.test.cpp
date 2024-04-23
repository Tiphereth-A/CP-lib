#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/util/josephus.hpp"

#include "../base.hpp"

vec<u64> Josephus_bf(u64 n, u64 k, u64 m) {
  assert(m && k && m <= n);
  assert(m <= 10000);
  vec<u64> ans(m);
  std::list<u64> l;
  for (u64 i = 0; i < n; ++i) l.push_back(i);
  auto it = l.begin();
  for (u32 i = 0; i < m; ++i) {
    for (u32 j = 1; j < k; ++j)
      if (++it == l.end()) it = l.begin();
    ans[i] = *it;
    if ((it = l.erase(it)) == l.end()) it = l.begin();
  }
  return ans;
}

void test(u64 n, u64 k) {
  u64 m = std::min(10000_u64, n);
  auto wants = Josephus_bf(n, k, m);
  for (u32 i = 1; i <= m; ++i) {
    u64 got = tifa_libs::util::Josephus(n, k, i);
    check(got, wants[i - 1], check_param(n), check_param(k), check_param(i));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test(10, 1); break;
    case tifa_libs::unittest::ts_example_01: test(10, 2); break;
    case tifa_libs::unittest::ts_random_00: test(10, 3); break;
    case tifa_libs::unittest::ts_random_01: test(1000, 1); break;
    case tifa_libs::unittest::ts_random_02: test(1000, 2); break;
    case tifa_libs::unittest::ts_random_03: test(1000, 3); break;
    case tifa_libs::unittest::ts_random_04: test(1000, 42); break;
    case tifa_libs::unittest::ts_random_05: test(1919810, 1); break;
    case tifa_libs::unittest::ts_random_06: test(1919810, 2); break;
    case tifa_libs::unittest::ts_random_07: test(1919810, 42); break;
    case tifa_libs::unittest::ts_random_08: test(1919810, 114514); break;
    case tifa_libs::unittest::ts_random_09: test(114514, 1919810); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}