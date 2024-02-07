#ifndef TIFALIBS_STR_HASH_SUBSTR
#define TIFALIBS_STR_HASH_SUBSTR

#include "../util/util.hpp"

namespace tifa_libs::str {

template <class mint, u32 base = 131>
class hash_substr {
  static inline vec<mint> p;
  vec<mint> hash;

 public:
  explicit constexpr hash_substr() {}

  constexpr void set(strnv s) {
    hash.resize(1, 0), hash.reserve(s.size() + 1);
    for (char c : s) hash.push_back(hash.back() * base + (u32)c + 1);
    if (p.size() <= s.size()) {
      if (p.empty()) p.push_back(1);
      p.reserve(s.size() + 1);
      while (p.size() <= s.size()) p.push_back(p.back() * base);
    }
  }
  constexpr u32 size() const { return u32(hash.size() - 1); }
  constexpr mint get(u32 pos, u32 len = -1_u32) const {
    assert(!p.empty() && pos < hash.size());
    return hash[pos + std::min(len, (u32)hash.size() - 1 - pos)] - hash[pos] * p[len];
  }
};

}  // namespace tifa_libs::str

#endif