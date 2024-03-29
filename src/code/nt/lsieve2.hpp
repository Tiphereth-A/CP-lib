#ifndef TIFALIBS_MATH_LSIEVE2
#define TIFALIBS_MATH_LSIEVE2

#include "../util/util.hpp"

namespace tifa_libs::math {

class lsieve2 {
  vec<ptt<u32>> pr;
  vec<u32> fr;

 public:
  explicit constexpr lsieve2(u32 n) : fr(n + 1) {
    for (u32 i = 2, x = n / 2, p1, p2, e; i <= n; x = n / (++i)) {
      if (!fr[i]) {
        for (p1 = 1, p2 = i, e = 0; p1 <= x; p1 = p2, p2 *= i, ++e) fr[p2] = 1;
        pr.emplace_back(i, e);
      }
      for (u32 t = 0; t < pr.size(); ++t)
        if (u32 p = pr[t].first; p > x) break;
        else if (i % p) fr[p * i] = i;
        else {
          fr[p * i] = fr[i];
          break;
        }
    }
  }

  // @param F: T(u32, u32)
  // @param %fpi(p, i) = $f(p^i)$
  // @return v[i] = f(i), for i in [0, n]
  template <class T, class F>
  requires requires(F f, u32 p, u32 i) {
    { f(p, i) } -> std::same_as<T>;
  }
  constexpr vec<T> run(F fpi, T init = T{1}) {
    vec<T> v(fr.size());
    v[1] = init;
    for (u32 i = 0; i < pr.size(); ++i)
      for (u32 p = pr[i].first, e = pr[i].second, pe = p, ex = 1; ex <= e; ++ex, pe *= p) v[pe] = fpi(p, ex);
    for (u32 i = 2; i < fr.size(); ++i) v[i] = v[i / fr[i]] * v[fr[i]];
    return v;
  }
};

}  // namespace tifa_libs::math

#endif