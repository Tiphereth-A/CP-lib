#define PROBLEM "https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces"

#include "../../include/io/ios_container.hpp"
#include "../../include/lalg/basis_z2.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    math::basisZ2<32, false> a;
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
    auto c = meet(a, b);
    vecu ans;
    for (auto x : c.basis)
      if (x.to_ulong()) ans.push_back((u32)x.to_ulong());
    std::cout << ans.size() << ' ' << ans << '\n';
  }
  return 0;
}
