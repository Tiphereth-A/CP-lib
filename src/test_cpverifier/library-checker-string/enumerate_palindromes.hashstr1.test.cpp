#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "../../code/util/util.hpp"
//
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_2e61n1.hpp"
#include "../../code/str/hash_substr.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_2e61n1>;
using hashstr = tifa_libs::str::hash_substr<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  {
    strn x;
    x.reserve(s.size() * 2 + 1);
    x.push_back('$');
    for (char c : s) x.push_back(c), x.push_back('$');
    s.swap(x);
  }
  strn t = s;
  std::ranges::reverse(t);
  hashstr hs, ht;
  hs.set(s), ht.set(t);
  u32 n = (u32)s.size();
  vecu ans(n);
  flt_ (u32, i, 0, n) {
    u32 l = 0, r = tifa_libs::min(i, n - 1 - i) + 1;
    while (l + 1 < r) {
      u32 m = (l + r) / 2, l_ = i - m, r_ = i + m;
      (hs.get(l_, r_ + 1 - l_) == ht.get(n - 1 - r_, r_ + 1 - l_) ? l : r) = m;
    }
    ans[i] = l;
  }
  for (u32 i = 1; i < n - 1; ++i) std::cout << ans[i] << " \n"[i + 2 == n];
  return 0;
}
