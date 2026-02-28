// competitive-verifier: STANDALONE

#include "../../../src/math/debruijn/lib.hpp"
#include "../../../src/math/qpow/basic/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
void test(u32 n, u32 k) {
  timer_(auto list = math::deBruijn(n, k));
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
  timer_(test(13, 2));
  timer_(test(7, 3));
  timer_(test(5, 5));
  timer_(test(4, 10));
  timer_(test(2, 26));
}