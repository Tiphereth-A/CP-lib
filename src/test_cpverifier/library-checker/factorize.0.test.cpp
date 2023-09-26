#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../../code/math/pfactors.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::i64 q;
  std::cin >> q;
  while (q--) {
    tifa_libs::u64 a;
    std::cin >> a;
    auto ans = tifa_libs::math::pfactors(a);
    tifa_libs::vec<tifa_libs::u64> pf;
    for (auto [k, v] : ans)
      for (tifa_libs::u32 i = 0; i < v; ++i) pf.push_back(k);
    std::cout << pf.size();
    if (!pf.empty())
      for (auto i : pf) std::cout << ' ' << i;
    std::cout << '\n';
  }
  return 0;
}
