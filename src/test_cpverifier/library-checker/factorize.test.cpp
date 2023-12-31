#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../../code/math/pfactors.hpp"
#include "../../code/util/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i64 q;
  std::cin >> q;
  while (q--) {
    u64 a;
    std::cin >> a;
    auto ans = tifa_libs::math::pfactors(a);
    vec<u64> pf;
    for (auto [k, v] : ans)
      for (u32 i = 0; i < v; ++i) pf.push_back(k);
    std::cout << pf.size();
    if (!pf.empty()) std::cout << ' ' << pf << '\n';
    std::cout << '\n';
  }
  return 0;
}
