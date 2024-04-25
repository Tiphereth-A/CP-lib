#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "../../code/util/util.hpp"
//
CEXP u32 MOD0 = 998244353;
CEXP u32 MOD1 = 1000000007;

#include "../../code/math/mint_ds.hpp"
#include "../../code/str/hash_substr2.hpp"

using mint0 = tifa_libs::math::mint_ds<-1>;
using mint1 = tifa_libs::math::mint_ds<-2>;
using hashstr = tifa_libs::str::hash_substr2<mint0, mint1>;

int main() {
  mint0::set_mod(MOD0);
  mint1::set_mod(MOD1);
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
