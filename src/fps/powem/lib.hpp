#pragma once

#include "../inv/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto powem_fps(poly_t CR f, poly_t g = {1}, u32 m = 0) NE {
  u32 n = (u32)f.size() - 1, k = 1, h = std::bit_ceil(n + 1);
  TPN poly_t::ccore_t core2, core4;
  core2.bzr(k * h * 2), core4.bzr(k * h * 4), g.resize(n + 1);
  if (!m || m > n) m = n;
  vec<TPN poly_t::val_t> p(k * h), q(k * h), pp(k * h * 4), qq(k * h * 4), rr(k * h * 2);
  flt_ (u32, i, 0, n + 1) p[i] = g[i], q[i] = -f[i];
  while (n) {
    pp.assign(k * h * 4, 0), qq.assign(k * h * 4, 0);
    flt_ (u32, i, 0, k) copy(begin(p) + i * h, begin(p) + i * h + n + 1, begin(pp) + i * h * 2);
    flt_ (u32, i, 0, k) copy(begin(q) + i * h, begin(q) + i * h + n + 1, begin(qq) + i * h * 2);
    qq[k * h * 2] += 1, core4.dif(pp), core4.dif(qq);
    for (u32 i = 0; i < k * h * 4; i += 2) swap(qq[i], qq[i + 1]);
    flt_ (u32, i, 0, k * h * 4) pp[i] *= qq[i];
    flt_ (u32, i, 0, k * h * 2) rr[i] = qq[i * 2] * qq[i * 2 + 1];
    core4.dit(pp), core2.dit(rr), rr[0] -= 1, p.assign(k * h, 0), q.assign(k * h, 0);
    flt_ (u32, i, 0, k * 2)
      flt_ (u32, j, 0, n / 2 + 1) p[i * h / 2 + j] = pp[i * h * 2 + j * 2 + n % 2], q[i * h / 2 + j] = rr[i * h + j];
    n /= 2, h /= 2, k *= 2;
  }
  poly_t s{begin(p), begin(p) + k}, t{begin(q), begin(q) + k};
  t.push_back(1), s.reverse(), t.reverse();
  return (s * inv_fps(t, m + 1)).pre(m + 1);
}

}  // namespace tifa_libs
