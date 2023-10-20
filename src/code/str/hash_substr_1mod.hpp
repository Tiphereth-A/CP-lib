#ifndef TIFA_LIBS_STR_HASH_SUBSTR_1MOD
#define TIFA_LIBS_STR_HASH_SUBSTR_1MOD

#include "../util/util.hpp"

namespace tifa_libs::str {

class hash_substr {
  constexpr static u64 mod = (1ull << 61) - 1, _2e30n1 = (1ul << 30) - 1, _2e31n1 = (1ul << 31) - 1;
  constexpr static u64 mul_(u64 a, u64 b) {
    u64 au = a >> 31, ad = a & _2e31n1, bu = b >> 31, bd = b & _2e31n1, _ = ad * bu + au * bd;
    return ((au * bu) << 1) + ad * bd + ((_ & _2e30n1) << 31) + (_ >> 30);
  }
  constexpr static u64 mod_(u64 a) {
    a = (a & mod) + (a >> 61);
    return a > mod ? a - mod : a;
  }

  u32 b;
  vec<u64> p, hash;
  bool need_reset;

 public:
  explicit hash_substr(u32 base) { set_base(base); }
  constexpr void set_base(u32 base) {
    assert(base > 128);
    b = base;
    need_reset = true;
  }
  void set(std::string_view s) {
    assert(need_reset);
    hash.resize(1, 0);
    hash.reserve(s.size() + 1);
    for (char c : s) hash.push_back(mod_(mul_(hash.back(), b) + (u64)c + 1));
    if (need_reset) {
      p.resize(1, 1);
      p.reserve(s.size() + 1);
      for (usz i = 0; i < s.size(); ++i) p.push_back(mod_(mul_(p.back(), b)));
      need_reset = false;
    }
  }
  constexpr u32 base() const { return b; }
  u64 get(usz pos, usz len = SIZE_MAX) const {
    assert(!need_reset && pos < hash.size());
    auto end_ = hash[pos + std::min(len, hash.size() - 1 - pos)];
    return mod_(end_ + mod * 7 - mul_(hash[pos], p[len]));
  }
};

}  // namespace tifa_libs::str

#endif