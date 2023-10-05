#ifndef TIFA_LIBS_STR_HASH_SUBSTR_2MOD
#define TIFA_LIBS_STR_HASH_SUBSTR_2MOD

#include "../util/util.hpp"

namespace tifa_libs::str {

class HashStr2 {
  const u64 m1, m2;
  u32 b;
  vec<ptt<u64>> p, hash;
  bool need_reset;

 public:
  HashStr2(u64 mod1, u64 mod2, u32 base) : m1(mod1), m2(mod2) { set_base(base); }
  constexpr void set_base(u32 base) {
    assert(base > 128);
    b = base;
    need_reset = true;
  }
  void set(std::string_view s) {
    assert(need_reset);
    hash.resize(1, {0, 0});
    hash.reserve(s.size() + 1);
    for (char c : s) hash.emplace_back((hash.back().first * b % m1 + (u64)c + 1) % m1, (hash.back().second * b % m2 + (u64)c + 1) % m2);
    if (need_reset) {
      p.resize(1, {1, 1});
      p.reserve(s.size() + 1);
      for (size_t i = 0; i < s.size(); ++i) p.emplace_back(p.back().first * b % m1, p.back().second * b % m2);
      need_reset = false;
    }
  }
  constexpr u32 base() const { return b; }
  ptt<u64> get(size_t pos, size_t len = SIZE_MAX) const {
    assert(!need_reset && pos < hash.size());
    auto end_ = hash[pos + std::min(len, hash.size() - 1 - pos)];
    return {(end_.first + m1 - hash[pos].first * p[len].first % m1) % m1, (end_.second + m2 - hash[pos].second * p[len].second % m2) % m2};
  }
};

}  // namespace tifa_libs::str

#endif