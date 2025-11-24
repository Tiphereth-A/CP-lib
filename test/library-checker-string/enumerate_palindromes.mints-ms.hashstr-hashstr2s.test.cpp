#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "../../include/util/alias_num.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_ms.hpp"
#include "../../include/str/hash_substr2.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, MOD>;
using namespace tifa_libs;
using mint0 = math::mint<math::mint_ms, 998244353>;
using mint1 = math::mint<math::mint_ms, 1000000007>;
using hashstr = str::hash_substr2<mint0, mint1>;

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
