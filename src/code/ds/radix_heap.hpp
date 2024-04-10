#ifndef TIFALIBS_DS_RADIX_HEAP
#define TIFALIBS_DS_RADIX_HEAP

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <std::unsigned_integral K, class V, class C = std::less<K>>
class radix_heap {
  static constexpr u32 B = sizeof(K) * 8;
  static constexpr C comp{};
  arr<vecp<K, V>, B + 1> vs;
  arr<K, B + 1> ms;
  u32 s;
  K last;

 public:
  constexpr explicit radix_heap() : s(0), last(0) { std::ranges::fill(ms, K(-1)); }

  constexpr u32 size() const { return s; }
  constexpr bool empty() const { return !s; }

  constexpr void emplace(K key, V const &val) {
    ++s;
    K b = (K)std::bit_width(key ^ last);
    vs[b].emplace_back(key, val), ms[b] = std::min(key, ms[b], comp);
  }

  constexpr std::pair<K, V> top() {
    if (!~ms[0]) {
      u32 idx = u32(std::ranges::find_if(ms, [](auto x) { return !!~x; }) - ms.begin());
      last = ms[idx];
      for (auto &p : vs[idx]) {
        K b = (K)std::bit_width(p.first ^ last);
        vs[b].emplace_back(p), ms[b] = std::min(p.first, ms[b], comp);
      }
      vs[idx].clear(), ms[idx] = K(-1);
    }
    return vs[0].back();
  }

  constexpr void pop() {
    top(), --s, vs[0].pop_back();
    if (vs[0].empty()) ms[0] = K(-1);
  }
};

}  // namespace tifa_libs::ds

#endif