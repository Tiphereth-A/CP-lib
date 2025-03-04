#ifndef TIFALIBS_STR_HASH_SUBSTR
#define TIFALIBS_STR_HASH_SUBSTR

#include "../util/alias_others.hpp"

namespace tifa_libs::str {

template <class mint, u32 base = 131>
class hash_substr {
  static inline vec<mint> p;
  vec<mint> hash;

 public:
  CEXP void set(strnv s) NE {
    const u32 n = (u32)s.size();
    for (hash.resize(1, 0), hash.reserve(n + 1); char c : s) hash.push_back(hash.back() * base + (u32)c + 1);
    if (p.size() <= n) {
      if (p.reserve(n + 1); p.empty()) p.push_back(1);
      while (p.size() <= n) p.push_back(p.back() * base);
    }
  }
  CEXP u32 size() CNE { return u32(hash.size() - 1); }
  CEXP mint get(u32 pos, u32 len = -1_u32) CNE {
    assert(!p.empty() && pos < hash.size());
    return hash[pos + min(len, (u32)hash.size() - 1 - pos)] - hash[pos] * p[len];
  }
};

}  // namespace tifa_libs::str

#endif