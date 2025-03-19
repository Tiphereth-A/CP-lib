#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_4_C"

#include "../../include/util/alias_others.hpp"
//

template <class T>
using hashfunc_t = chash<T>;
template <class T>
using hashset = std::unordered_set<T, std::conditional_t<std::is_void_v<hashfunc_t<T>>, std::hash<T>, hashfunc_t<T>>>;

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
