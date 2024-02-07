#ifndef TIFALIBS_STR_HASH_SUBSTR2
#define TIFALIBS_STR_HASH_SUBSTR2

#include "hash_substr.hpp"

namespace tifa_libs::str {

template <class mint0, class mint1, u32 base = 131>
class hash_substr2 {
  hash_substr<mint0, base> h0;
  hash_substr<mint1, base> h1;

 public:
  explicit constexpr hash_substr2() {}

  constexpr void set(strnv s) { h0.set(s), h1.set(s); }
  constexpr u32 size() const { return h0.size(); }
  constexpr std::pair<mint0, mint1> get(u32 pos, u32 len = -1_u32) const { return {h0.get(pos, len), h1.get(pos, len)}; }
};

}  // namespace tifa_libs::str

#endif