#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../../include/io/ios_container.hpp"
#include "../../include/nt/pfactors.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 q;
  std::cin >> q;
  while (q--) {
    u64 a;
    std::cin >> a;
    auto ans = math::pfactors<false>(a);
    std::cout << ans.size();
    if (!ans.empty()) std::cout << ' ' << ans;
    std::cout << '\n';
  }
  return 0;
}
