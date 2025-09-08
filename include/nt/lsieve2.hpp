#ifndef TIFALIBS_MATH_LSIEVE2
#define TIFALIBS_MATH_LSIEVE2

#include "../util/alias_others.hpp"

namespace tifa_libs::math {

class lsieve2 {
  vecptu pr;
  vecu fr;

 public:
  CEXPE lsieve2(u32 n) NE : fr(n + 1) {
    for (u32 i = 2, x = n / 2, p1, p2, e; i <= n; x = n / (++i)) {
      if (!fr[i]) {
        for (p1 = 1, p2 = i, e = 0; p1 <= x; p1 = p2, p2 *= i, ++e) fr[p2] = 1;
        pr.emplace_back(i, e);
      }
      for (auto [p, _] : pr)
        if (p > x) break;
        // p <= x == n/i ==> p*i <= n
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
  CEXP vec<T> run(F fpi, T init = T{1}) CNE {
    vec<T> v(fr.size());
    if (fr.size() < 2) return v;
    v[1] = init;
    flt_ (u32, i, 0, (u32)pr.size())
      for (u32 p = pr[i].first, e = pr[i].second, pe = p, ex = 1; ex <= e; ++ex, pe *= p) v[pe] = fpi(p, ex);
    flt_ (u32, i, 2, (u32)fr.size()) v[i] = v[i / fr[i]] * v[fr[i]];
    return v;
  }
};

}  // namespace tifa_libs::math

#endif