#ifndef TIFALIBS_MATH_CRT_MOD
#define TIFALIBS_MATH_CRT_MOD

#include "../math/safe_mod.hpp"
#include "inv_gcd.hpp"

namespace tifa_libs::math {

template <uint_c T = u64>
CEXP auto crt_mod(vec<T> CR r, vec<T> m, u64 const mod) NE {
  static_assert(sizeof(T) >= 8);
  using S = to_sint_t<T>;
  std::optional<ptt<T>> ret;
  const u32 l = (u32)m.size();
  assert(r.size() == l);
  m.push_back(mod);
  vec<T> p(l + 1, 1), x(l + 1);
  flt_ (u32, i, 0, l) {
    T b = r[i], n = m[i];
    assert(n > 0);
    auto [g, ip] = inv_gcd(p[i], n);
    S q = S(b - x[i]) / (S)g;
    if (S(b - x[i]) % (S)g) return ret;
    n /= g;
    T t = (T)safe_mod(q % (S)n * (S)ip, n);
    flt_ (u32, j, i + 1, l + 1) (x[j] += t * p[j]) %= m[j], (p[j] *= n) %= m[j];
  }
  ret.emplace(x.back(), p.back());
  return ret;
}

}  // namespace tifa_libs::math

#endif