#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/math/debruijn.hpp"

#include "../../../include/math/qpow.hpp"
#include "../base.hpp"

using namespace tifa_libs;
void test(u32 n, u32 k) {
  auto list = math::deBruijn(n, k);
  usz len = math::qpow<u64>(k, n);
  check(list.size(), len, check_param(n), check_param(k));

  vecu text = list;
  for (auto i : list) text.push_back(i);
  vecu pattern(n);
  flt_ (usz, cnt, 0, len) {
    auto res = std::search(begin(text), end(text), std::boyer_moore_horspool_searcher(begin(pattern), end(pattern)));
    check_bool(res != end(text), check_param(text), check_param(pattern));
    ++pattern.back();
    for (u32 i = n - 1; i && pattern[i] == k; --i) {
      pattern[i] = 0;
      ++pattern[i - 1];
    }
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test(13, 2); break;
    case unittest::TC::example_01: test(7, 3); break;
    case unittest::TC::random_00: test(5, 5); break;
    case unittest::TC::random_01: test(4, 10); break;
    case unittest::TC::random_02: test(2, 26); break;
    case unittest::TC::random_03: break;
    case unittest::TC::random_04: break;
    case unittest::TC::random_05: break;
    case unittest::TC::random_06: break;
    case unittest::TC::random_07: break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}