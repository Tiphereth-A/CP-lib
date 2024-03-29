#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "../../code/util/util.hpp"

constexpr u32 MOD0 = 998244353;
constexpr u32 MOD1 = 1000000007;

#include "../../code/math/mint_s30.hpp"
#include "../../code/str/hash_substr2.hpp"

using mint0 = tifa_libs::math::mint_s30<MOD0>;
using mint1 = tifa_libs::math::mint_s30<MOD1>;
using hashstr = tifa_libs::str::hash_substr2<mint0, mint1>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
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
  std::reverse(t.begin(), t.end());
  hashstr hs, ht;
  hs.set(s), ht.set(t);
  u32 n = (u32)s.size();
  vec<u32> ans(n);
  for (u32 i = 0; i < n; ++i) {
    u32 l = 0, r = std::min(i, n - 1 - i) + 1;
    while (l + 1 < r) {
      u32 m = (l + r) / 2, l_ = i - m, r_ = i + m;
      (hs.get(l_, r_ + 1 - l_) == ht.get(n - 1 - r_, r_ + 1 - l_) ? l : r) = m;
    }
    ans[i] = l;
  }
  for (u32 i = 1; i < n - 1; ++i) std::cout << ans[i] << " \n"[i + 2 == n];
  return 0;
}
