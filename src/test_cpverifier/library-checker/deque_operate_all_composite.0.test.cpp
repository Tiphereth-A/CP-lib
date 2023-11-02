#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"

#include "../../code/ds/deque_with_w.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using T = ptt<mint>;
T e() { return T{1, 0}; }
T op(T b, T a) { return T{a.first * b.first, a.first * b.second + a.second}; }
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  tifa_libs::ds::deque_with_w<T, e, op> deq;
  for (u32 i = 0, opt; i < n; ++i) {
    std::cin >> opt;
    mint a, b;
    if (opt == 0) std::cin >> a >> b, deq.push_front({a, b});
    else if (opt == 1) std::cin >> a >> b, deq.push_back({a, b});
    else if (opt == 2) deq.pop_front();
    else if (opt == 3) deq.pop_back();
    else {
      std::cin >> a;
      auto ret = deq.w();
      std::cout << ret.first * a + ret.second << '\n';
    }
  }
  return 0;
}
