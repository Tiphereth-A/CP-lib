#ifndef TIFALIBS_MATH_FACT_HELPER
#define TIFALIBS_MATH_FACT_HELPER

#include "../util/traits.hpp"

namespace tifa_libs::math {

template <mint_c mint>
struct fact_helper {
  using val_t = mint;
  static CEXP u32 DEFUALT_MAX = 10'000'001;
  static CEXP u64 mod() NE { return val_t::mod(); }
  static inline vec<val_t> fact, ifact;

  fact_helper() = delete;

  // ensure fact.size() >= sz
  static CEXP void ensure(u32 sz = DEFUALT_MAX) NE {
    if (sz = max(2_u32, min((u32)mod(), sz)); sz <= fact.size()) return;
    u32 pre = (u32)fact.size();
    fact.resize(sz), ifact.resize(sz);
    if (pre < 2) pre = 2, fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
    flt_ (u32, i, pre, sz) fact[i] = fact[i - 1] * i;
    ifact.back() = fact.back().inv();
    for (u32 i = sz - 1; i > pre; --i) ifact[i - 1] = ifact[i] * i;
  }

  static CEXP val_t get_fact(u64 n) NE {
    if (n >= mod()) [[unlikely]]
      return 0;
    if (fact.empty()) [[unlikely]]
      ensure();
    if (n < fact.size()) [[likely]]
      return fact[n];
    val_t _ = fact.back() * n;
    flt_ (u64, i, fact.size(), n) _ *= i;
    return _;
  }
  static CEXP val_t get_ifact(u64 n) NE {
    if (n >= mod()) [[unlikely]]
      return 0;
    if (fact.empty()) [[unlikely]]
      ensure();
    if (n < ifact.size()) [[likely]]
      return ifact[n];
    return get_fact(n).inv();
  }
};

}  // namespace tifa_libs::math

#endif