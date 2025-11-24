#ifndef TIFALIBS_DS_RADIX_HEAP
#define TIFALIBS_DS_RADIX_HEAP

#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

template <std::unsigned_integral K, class V, class C = std::less<K>>
class radix_heap {
  static CEXP u32 B = sizeof(K) * 8;
  static CEXP C comp{};
  arr<vecp<K, V>, B + 1> vs;
  arr<K, B + 1> ms;
  u32 s;
  K last;

 public:
  CEXP radix_heap() NE : s{0}, last{0} { fill(ms, K(-1)); }

  CEXP u32 size() CNE { return s; }
  CEXP bool empty() CNE { return !s; }
  CEXP void emplace(K key, cT_(V) val) NE {
    const K b = (K)std::bit_width(key ^ last);
    ++s, vs[b].emplace_back(key, val), ms[b] = min(key, ms[b], comp);
  }
  CEXP std::pair<K, V> top() NE {
    if (!~ms[0]) {
      const u32 idx = u32(find_if(ms, [](auto x) NE { return !!~x; }) - begin(ms));
      for (last = ms[idx]; auto& p : vs[idx]) {
        const K b = (K)std::bit_width(p.first ^ last);
        vs[b].emplace_back(p), ms[b] = min(p.first, ms[b], comp);
      }
      vs[idx].clear(), ms[idx] = K(-1);
    }
    return vs[0].back();
  }

  CEXP void pop() NE {
    if (top(), --s, vs[0].pop_back(); vs[0].empty()) ms[0] = K(-1);
  }
};

template <class K, class V>
using rheap = std::conditional_t<std::unsigned_integral<K>, ds::radix_heap<K, V>, pqg<std::pair<K, V>>>;
template <class K, class V>
using rheapg = std::conditional_t<std::unsigned_integral<K>, ds::radix_heap<K, V, std::greater<K>>, pq<std::pair<K, V>>>;

}  // namespace tifa_libs::ds

#endif