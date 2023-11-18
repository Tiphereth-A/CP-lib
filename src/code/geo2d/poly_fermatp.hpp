#ifndef TIFA_LIBS_GEO2D_POLY_FERMATP
#define TIFA_LIBS_GEO2D_POLY_FERMATP

#include "../rand/gen.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

// simulated annealing
template <class FP>
point<FP> fermatp(polygon<FP> const &po, const FP begin = 1e10, const FP end = EPS<FP>, const FP delta = .999) {
  static rand::Gen<std::uniform_real_distribution<FP>> gen_angle(0, 2 * PI<FP>);
  point<FP> ret = po.vs.front(), pre = po.vs.front(), now;
  FP dis_ret{}, dis_pre{}, dis_now;
  for (u32 i = 1; i < po.vs.size(); ++i) dis_pre += dist_PP(po.vs[i], ret);
  dis_ret = dis_pre;
  for (FP T = begin; T > end; T *= delta) {
    now = pre + make_P_polar(T, gen_angle());
    dis_now = 0;
    for (u32 i = 0; i < po.vs.size(); ++i) dis_now += dist_PP(po.vs[i], now);
    if (is_lt(dis_now, dis_ret)) {
      ret = now;
      dis_ret = dis_now;
    }
    if (!is_gt(dis_now, dis_pre) || std::exp((dis_pre - dis_now) / T) > gen_angle() / gen_angle.distrib().max()) {
      pre = now;
      dis_pre = dis_now;
    }
  }
  return ret;
}

}  // namespace tifa_libs::geo

#endif