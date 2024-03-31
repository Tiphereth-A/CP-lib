#ifndef TIFALIBS_LALG_MAT_CHARPOLY
#define TIFALIBS_LALG_MAT_CHARPOLY

#include "mat.hpp"
#include "mat_uhb.hpp"

namespace tifa_libs::math {

template <class T, class Is0>
requires requires(Is0 is0, T t) {
  { is0(t) } -> std::same_as<bool>;
}
constexpr vec<T> charpoly(matrix<T> mat, Is0 &&is0) {
  u32 n = mat.row();
  assert(n == mat.col());
  uhb(mat, std::forward<Is0>(is0));
  vvec<T> p(n + 1);
  p[0].resize(1);
  p[0][0] = 1;
  p[1].resize(2);
  p[1][0] = -mat(0, 0);
  p[1][1] = 1;
  for (u32 i = 2; i <= n; ++i) {
    vec<T> const &pc = p[i - 1];
    vec<T> &pi = p[i];
    pi.resize(p[i - 1].size() + 1);
    for (u32 j = 0, _ = (u32)pc.size(); j < _; ++j) pi[j] += pc[j] * -mat(i - 1, i - 1);
    for (u32 j = 0, _ = (u32)pc.size(); j < _; ++j) pi[j + 1] += pc[j];
    T t = 1;
    for (u32 j = 1; j < i; ++j) {
      T _ = (t *= mat(i - j, i - j - 1)) * mat(i - j - 1, i - 1);
      if (is0(_)) continue;
      for (u32 k = 0; k <= i - j - 1; ++k) pi[k] -= _ * p[i - j - 1][k];
    }
  }
  return p[n];
}

}  // namespace tifa_libs::math

#endif