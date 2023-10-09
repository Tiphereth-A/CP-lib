#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"

#include "../../code/comb/exlucas.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 t, m;
  std::cin >> t >> m;
  if (m == 1) {
    while (t--) std::cout << "0\n";
  } else {
    tifa_libs::math::ExLucas mCn(m);
    while (t--) {
      tifa_libs::i64 n, k;
      std::cin >> n >> k;
      std::cout << mCn(n, k) << '\n';
    }
  }
  return 0;
}
