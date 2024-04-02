#ifndef TIFALIBS_MATH_INTERP_NEWTON_N2
#define TIFALIBS_MATH_INTERP_NEWTON_N2

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
class interp_newton {
  // {(x_0,y_0),(x__1,y_1),...,(x_{n-1},y_{n-1})}
  vecpt<T> points;
  // diffs[r][l] = f[x_l,x_{l+1},...,x_r]
  vvec<T> diffs;
  // (x-x_0)(x-x_1)...(x-x_{n-1})
  vec<T> base;
  // f[x_0]+f[x_0,x_1](x-x_0)+...+f[x_0,x_1,...,x_n](x-x_0)(x-x_1)...(x-x_{n-1})
  vec<T> fit;

 public:
  explicit constexpr interp_newton() {}
  constexpr interp_newton &insert(T const &x, T const &y) {
    points.emplace_back(x, y);
    u32 n = (u32)points.size();
    if (n == 1) {
      base.push_back(1);
    } else {
      u32 m = (u32)base.size();
      base.push_back(0);
      for (u32 i = m; i; --i) base[i] = base[i - 1];
      base[0] = 0;
      for (u32 i = 0; i < m; ++i) base[i] = base[i] - points[n - 2].first * base[i + 1];
    }
    diffs.emplace_back(points.size());
    diffs[n - 1][n - 1] = y;
    if (n > 1)
      for (u32 i = n - 2; ~i; --i) diffs[n - 1][i] = (diffs[n - 2][i] - diffs[n - 1][i + 1]) / (points[i].first - points[n - 1].first);
    fit.push_back(0);
    for (u32 i = 0; i < n; ++i) fit[i] = fit[i] + diffs[n - 1][0] * base[i];
    return *this;
  }
  constexpr vec<T> coeffs() const { return fit; }
  constexpr T eval(T const &x) {
    T ans{};
    for (auto it = fit.rbegin(); it != fit.rend(); ++it) ans = ans * x + *it;
    return ans;
  }
};

}  // namespace tifa_libs::math

#endif