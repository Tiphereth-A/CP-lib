#define PROBLEM "https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces"

#include "../../code/io/ios_container.hpp"
#include "../../code/math/basis_z2.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::math::basisZ2<32> a;
    u32 n, m;
    std::cin >> n;
    for (u32 i = 0, x; i < n; ++i) {
      std::cin >> x;
      a.insert(x);
    }
    std::cin >> m;
    vec<std::bitset<32>> b;
    b.reserve(m);
    for (u32 i = 0, x; i < m; ++i) {
      std::cin >> x;
      b.emplace_back(x);
    }
    auto c = a.meet(b);
    vecu ans;
    for (auto x : c.basis)
      if (x.to_ulong()) ans.push_back(x.to_ulong());
    std::cout << ans.size() << ' ' << ans << '\n';
  }
  return 0;
}
