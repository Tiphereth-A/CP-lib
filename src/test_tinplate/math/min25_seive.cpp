#define PROBLEM "https://www.luogu.com.cn/problem/P5325"

#include "../../code/math/min25_seive.hpp"

#include "../../code/math/mint_ss.hpp"
#include "../../code/math/qpow.hpp"

using mint = tifa_libs::math::mint_ss<1'000'000'000 + 7>;

mint f(u64 p, u64 c) {
  auto _ = tifa_libs::math::qpow(mint(p), c);
  return _ * (_ - 1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;

  tifa_libs::math::min25_seive<mint, f> min25(n);
  auto h1 = min25.sum_pk(1), h2 = min25.sum_pk(2);
  for (usz i = 1; i < h2.size(); ++i) h2[i] -= h1[i];
  std::cout << min25.run(h2) << '\n';
  return 0;
}
