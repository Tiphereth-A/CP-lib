#ifndef TIFALIBS_STR_HASH_SUBSTR_2D
#define TIFALIBS_STR_HASH_SUBSTR_2D

#include "hash_substr.hpp"

namespace tifa_libs::str {

template <class mint, u32 base = 131, u32 base2 = 137>
class hash_substr_2d {
  static inline vec<mint> p;
  vec<hash_substr<mint, base>> hs;
  vvec<mint> hash;

 public:
  CEXP void set(spn<strn> s, u32 len_c) {
    const u32 n = (u32)s.size(), m = (u32)s[0].size();
    if (assert(0 < len_c && len_c <= m), hs.resize(n), hash = vvec<mint>(n + 1, vec<mint>(m + 1)); p.size() <= n) {
      if (p.reserve(n + 1); p.empty()) p.push_back(1);
      while (p.size() <= n) p.push_back(p.back() * base2);
    }
    flt_ (u32, i, 0, n) hs[i].set(s[i]);
    fle_ (u32, i, 1, n)
      fle_ (u32, j, 1, m) hash[i][j] = hash[i - 1][j] * base2 + hs[i - 1].get(j - 1, len_c);
  }
  CEXP u32 row() const { return u32(hash.size() - 1); }
  CEXP u32 col() const { return u32(hash[0].size() - 1); }
  CEXP mint get(u32 r, u32 c, u32 len_r = -1_u32) const {
    assert(!hs.empty() && r < hash.size() && c < hash[0].size());
    return hash[r + min(len_r, (u32)hash.size() - 1 - r)][c + 1] - hash[r][c + 1] * p[len_r];
  }
};

}  // namespace tifa_libs::str

#endif