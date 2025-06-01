#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_4_C"

#include "../../include/util/alias_others.hpp"
//
#include "../../include/edh/hash_splitmix64.hpp"

using namespace tifa_libs;
template <class>
using hashfunc_t = hash_splitmix64;
using namespace tifa_libs;
template <class T>
using hashset = __gnu_pbds::cc_hash_table<T, __gnu_pbds::null_type, std::conditional_t<std::is_void_v<hashfunc_t<T>>, typename __gnu_pbds::detail::default_hash_fn<T>::type, hashfunc_t<T>>>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  hashset<u64> dict;
  flt_ (u32, i, 0, n) {
    strn s, t;
    std::cin >> s >> t;
    u64 x = 0;
    for (char c : t) switch (c) {
        case 'A': ++x; [[fallthrough]];
        case 'C': ++x; [[fallthrough]];
        case 'G': ++x; [[fallthrough]];
        default: (++x) *= 5;
      }
    if (s[0] == 'i')
      dict.insert(x);
    else
      std::cout << (dict.find(x) != dict.end() ? "yes\n" : "no\n");
  }
  return 0;
}
