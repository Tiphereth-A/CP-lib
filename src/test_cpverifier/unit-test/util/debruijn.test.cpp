#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/util/debruijn.hpp"

#include "../../../code/math/qpow.hpp"
#include "../base.hpp"

void test(u32 n, u32 k) {
  auto list = tifa_libs::util::deBruijn(n, k);
  usz len = tifa_libs::math::qpow<u64>(k, n);
  check(list.size(), len, check_param(n), check_param(k));

  vecu text = list;
  for (auto i : list) text.push_back(i);
  vecu pattern(n);
  for (usz cnt = 0; cnt < len; ++cnt) {
    auto res = std::search(text.begin(), text.end(), std::boyer_moore_horspool_searcher(pattern.begin(), pattern.end()));
    check_bool(res != text.end(), check_param(text), check_param(pattern));
    ++pattern.back();
    for (u32 i = n - 1; i && pattern[i] == k; --i) {
      pattern[i] = 0;
      ++pattern[i - 1];
    }
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test(13, 2); break;
    case tifa_libs::unittest::ts_example_01: test(7, 3); break;
    case tifa_libs::unittest::ts_random_00: test(5, 5); break;
    case tifa_libs::unittest::ts_random_01: test(4, 10); break;
    case tifa_libs::unittest::ts_random_02: test(2, 26); break;
    case tifa_libs::unittest::ts_random_03: break;
    case tifa_libs::unittest::ts_random_04: break;
    case tifa_libs::unittest::ts_random_05: break;
    case tifa_libs::unittest::ts_random_06: break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}