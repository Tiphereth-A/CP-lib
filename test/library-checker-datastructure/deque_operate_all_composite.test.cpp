#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"

#include "../../include/ds/deque_with_w.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_ms.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, 998244353>;
using T = ptt<mint>;
T e() { return T{1, 0}; }
T op(T b, T a) { return T{a.first * b.first, a.first * b.second + a.second}; }
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  ds::deque_with_w<T, e, op> deq;
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
