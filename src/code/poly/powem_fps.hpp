#ifndef TIFALIBS_POLY_POWEM_FPS
#define TIFALIBS_POLY_POWEM_FPS

#include "inv_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> powem_fps(poly<mint, ccore> CR f, poly<mint, ccore> g = {1}, u32 m = 0) {
  using poly_t = poly<mint, ccore>;
  u32 n = (u32)f.size() - 1, k = 1, h = std::bit_ceil(n + 1);
  ccore core2, core4;
  core2.bzr(k * h * 2), core4.bzr(k * h * 4), g.resize(n + 1);
  if (!m || m > n) m = n;
  vec<mint> p(k * h), q(k * h), pp(k * h * 4), qq(k * h * 4), rr(k * h * 2);
  fle_ (u32, i, 0, n) p[i] = g[i], q[i] = -f[i];
  while (n) {
    pp.assign(k * h * 4, 0), qq.assign(k * h * 4, 0);
    flt_ (u32, i, 0, k) std::copy(p.begin() + i * h, p.begin() + i * h + n + 1, pp.begin() + i * h * 2);
    flt_ (u32, i, 0, k) std::copy(q.begin() + i * h, q.begin() + i * h + n + 1, qq.begin() + i * h * 2);
    qq[k * h * 2] += 1, core4.dif(pp), core4.dif(qq);
    for (u32 i = 0; i < k * h * 4; i += 2) swap(qq[i], qq[i + 1]);
    flt_ (u32, i, 0, k * h * 4) pp[i] *= qq[i];
    flt_ (u32, i, 0, k * h * 2) rr[i] = qq[i * 2] * qq[i * 2 + 1];
    core4.dit(pp), core2.dit(rr), rr[0] -= 1, p.assign(k * h, 0), q.assign(k * h, 0);
    flt_ (u32, i, 0, k * 2)
      fle_ (u32, j, 0, n / 2) p[i * h / 2 + j] = pp[i * h * 2 + j * 2 + n % 2], q[i * h / 2 + j] = rr[i * h + j];
    n /= 2, h /= 2, k *= 2;
  }
  poly_t s{p.begin(), p.begin() + k}, t{q.begin(), q.begin() + k};
  return t.data().push_back(1), s.reverse(), t.reverse(), (s * inv_fps(t, m + 1)).pre(m + 1);
}

}  // namespace tifa_libs::math

#endif