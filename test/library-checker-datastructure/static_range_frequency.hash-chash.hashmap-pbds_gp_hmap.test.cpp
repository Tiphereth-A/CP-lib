#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

#include "../../include/util/alias_others.hpp"
//

using namespace tifa_libs;
template <class T>
using hashfunc_t = chash<T>;
using namespace tifa_libs;
template <class K, class V>
using hashmap = __gnu_pbds::gp_hash_table<K, V, std::conditional_t<std::is_void_v<hashfunc_t<K>>, typename __gnu_pbds::detail::default_hash_fn<K>::type, hashfunc_t<K>>>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vecu a(n);
  for (auto& i : a) std::cin >> i;
  hashmap<u32, vecu> hm;
  flt_ (u32, i, 0, n) hm[a[i]].push_back(i);
  flt_ (u32, i, 1, q + 1, l, r, x) {
    std::cin >> l >> r >> x;
    if (l == r) {
      std::cout << "0\n";
      continue;
    }
    auto CR now = hm[x];
    auto it1 = std::ranges::lower_bound(now, l), it2 = std::ranges::upper_bound(now, r - 1);
    std::cout << it2 - it1 << '\n';
  }
  return 0;
}
