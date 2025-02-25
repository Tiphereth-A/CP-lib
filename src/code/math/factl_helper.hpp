#ifndef TIFALIBS_MATH_FACTL_HELPER
#define TIFALIBS_MATH_FACTL_HELPER

#include "../poly/ctsh_fps.hpp"
#include "fact_helper.hpp"

namespace tifa_libs::math {

template <class poly_t>
struct factl_helper : fact_helper<TPN poly_t::val_t> {
  using val_t = TPN poly_t::val_t;
  using base_t = fact_helper<TPN poly_t::val_t>;
  static CEXP u32 LBSZ = 9;
  static CEXP u32 SZ = 1 << LBSZ;
  static CEXP u32 threshold = 2'000'001;
  static_assert(threshold > SZ * 2);

  factl_helper() = delete;
  static CEXP void ensure(u32 sz = threshold) NE {
    if (sz < threshold) [[unlikely]]
      sz = threshold;
    base_t::ensure(sz);
  }
  static CEXP val_t get_fact(u64 n) NE {
    if (n >= base_t::mod()) [[unlikely]]
      return 0;
    if (base_t::fact.size() < threshold) [[unlikely]]
      base_t::ensure(threshold);
    return n < base_t::fact.size() ? base_t::fact[n] : fact_(n);
  }
  static CEXP val_t get_ifact(u64 n) NE {
    if (n >= base_t::mod()) [[unlikely]]
      return 0;
    if (base_t::fact.size() < threshold) [[unlikely]]
      base_t::ensure(threshold);
    return n < base_t::fact.size() ? base_t::ifact[n] : fact_(n).inv();
  }

 private:
  // mod() / SZ
  static inline u64 B;
  // f[i] = (i*B + 1) * ... * (i*B + B)
  static inline poly_t f;
  static val_t fact_(u64 n) NE {
    static bool inited = false;
    if (!inited) {
      inited = true;
      B = base_t::mod() >> LBSZ;
      f.reserve(SZ), f[0] = 1;
      flt_ (u32, i, 0, LBSZ) {
        poly_t g = ctsh_fps(f, val_t(1 << i), base_t::ifact, 3_u32 << i);
        const auto get = [&](u32 j) { return j < (1_u32 << i) ? f[j] : g[j - (1 << i)]; };
        f.resize(2_u32 << i);
        flt_ (u32, j, 0, 2_u32 << i) f[j] = get(2 * j) * get(2 * j + 1) * ((2 * j + 1) << i);
      }
      if (B > SZ) {
        vec<val_t> g = ctsh_fps(f, val_t(SZ), base_t::ifact, u32(B - SZ));
        move(g, std::back_inserter(f));
      } else f.resize(B);
      flt_ (u32, i, 0, (u32)B) f[i] *= val_t(i + 1) * SZ;
      f.insert(f.begin(), 1);
      flt_ (u32, i, 0, (u32)B) f[i + 1] *= f[i];
    }
    val_t res;
    u64 q = n / SZ;
    u32 r = n % SZ;
    if (2 * r <= SZ) {
      res = f[q];
      flt_ (u32, i, 0, r) res *= n - i;
    } else if (q != B) {
      res = f[q + 1];
      val_t den = 1;
      flt_ (u32, i, 1, SZ - r + 1) den *= n + i;
      res /= den;
    } else {
      res = base_t::mod() - 1;
      val_t den = 1;
      flt_ (u64, i, n + 1, base_t::mod()) den *= i;
      res /= den;
    }
    return res;
  }
};

}  // namespace tifa_libs::math

#endif