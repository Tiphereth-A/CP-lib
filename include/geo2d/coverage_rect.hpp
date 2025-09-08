#ifndef TIFALIBS_GEO2D_COVERAGE_RECT
#define TIFALIBS_GEO2D_COVERAGE_RECT

#include "cvh.hpp"

namespace tifa_libs::geo {

// clang-format off
enum class CVHRECT : u8 { min_area, min_circum };
// clang-format on

// Coverage rectangle with min circum
template <CVHRECT type, class FP>
CEXP polygon<FP> coverage_rect(cT_(cvh<FP>) ch) NE {
  const u32 n = ch.size();
  retif_((n == 0) [[unlikely]], ch);
  if (n == 1) return {{ch[0], ch[0], ch[0], ch[0]}};
  if (n == 2) return {{ch[0], ch[0], ch[1], ch[1]}};
  FP ans = std::numeric_limits<FP>::max();
  u32 r = 1, p = 1, q = 1, ans_i = 0, ans_r = 0, ans_p = 0, ans_q = 0;
  flt_ (u32, i, 0, n) {
    const auto ni = ch.next(i);
    while (!is_neg(cross(ch.vs[i], ch.vs[ni], ch.vs[ch.next(r)]) -
                   cross(ch.vs[i], ch.vs[ni], ch.vs[r]))) r = ch.next(r);
    while (!is_neg(dot(ch.vs[i], ch.vs[ni], ch.vs[ch.next(p)]) -
                   dot(ch.vs[i], ch.vs[ni], ch.vs[p]))) p = ch.next(p);
    if (i == 0) q = p;
    while (!is_pos(dot(ch.vs[i], ch.vs[ni], ch.vs[ch.next(q)]) -
                   dot(ch.vs[i], ch.vs[ni], ch.vs[q]))) q = ch.next(q);
    FP _;
    if CEXP (type == CVHRECT::min_area)
      _ = cross(ch.vs[i], ch.vs[ni], ch.vs[r]) *
          (dot(ch.vs[i], ch.vs[ni], ch.vs[p]) - dot(ch.vs[i], ch.vs[ni], ch.vs[q])) /
          (ch.vs[i] - ch.vs[ni]).norm2();
    else if CEXP (type == CVHRECT::min_circum)
      _ = (cross(ch.vs[i], ch.vs[ni], ch.vs[r]) +
           (dot(ch.vs[i], ch.vs[ni], ch.vs[p]) - dot(ch.vs[i], ch.vs[ni], ch.vs[q]))) /
          (ch.vs[i] - ch.vs[ni]).abs();
    if (ans > _) ans = _, ans_i = i, ans_r = r, ans_p = p, ans_q = q;
  }
  point dir = line{ch[ans_i], ch[ch.next(ans_i)]}.direction(), vdir = rot90(dir);
  line li{ch[ans_i], ch[ans_i] + dir},
      lp{ch[ans_p], ch[ans_p] + vdir},
      lr{ch[ans_r], ch[ans_r] + dir},
      lq{ch[ans_q], ch[ans_q] + vdir};
  return {{ins_LL(li, lp), ins_LL(lp, lr), ins_LL(lr, lq), ins_LL(lq, li)}};
}

}  // namespace tifa_libs::geo

#endif