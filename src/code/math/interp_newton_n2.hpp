#ifndef TIFALIBS_MATH_INTERP_NEWTON_N2
#define TIFALIBS_MATH_INTERP_NEWTON_N2

#include "../util/alias_others.hpp"

namespace tifa_libs::math {

template <class T>
class interp_newton {
  // {(x_0,y_0),(x__1,y_1),...,(x_{n-1},y_{n-1})}
  vecpt<T> p;
  // ds[r][l] = f[x_l,x_{l+1},...,x_r]
  vvec<T> ds;
  // (x-x_0)(x-x_1)...(x-x_{n-1})
  vec<T> b;
  // f[x_0]+f[x_0,x_1](x-x_0)+...+f[x_0,x_1,...,x_n](x-x_0)(x-x_1)...(x-x_{n-1})
  vec<T> fit;

 public:
  CEXP interp_newton &insert(cT_(T) x, cT_(T) y) NE {
    p.emplace_back(x, y);
    const u32 n = (u32)p.size();
    if (n == 1) b.push_back(1);
    else {
      u32 m = (u32)b.size();
      b.push_back(0);
      for (u32 i = m; i; --i) b[i] = b[i - 1];
      b[0] = 0;
      flt_ (u32, i, 0, m) b[i] = b[i] - p[n - 2].first * b[i + 1];
    }
    ds.emplace_back(p.size()), ds[n - 1][n - 1] = y;
    if (n > 1)
      for (u32 i = n - 2; ~i; --i) ds[n - 1][i] = (ds[n - 2][i] - ds[n - 1][i + 1]) / (p[i].first - p[n - 1].first);
    fit.push_back(0);
    flt_ (u32, i, 0, n) fit[i] = fit[i] + ds[n - 1][0] * b[i];
    return *this;
  }
  CEXP vec<T> coeffs() CNE { return fit; }
  CEXP T eval(cT_(T) x) NE {
    T ans{};
    for (auto it = fit.rbegin(); it != fit.rend(); ++it) ans = ans * x + *it;
    return ans;
  }
};

}  // namespace tifa_libs::math

#endif