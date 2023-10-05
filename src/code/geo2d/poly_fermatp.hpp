#ifndef TIFA_LIBS_GEO2D_POLY_FERMATP
#define TIFA_LIBS_GEO2D_POLY_FERMATP

#include "polygon.hpp"

namespace tifa_libs::geo {

// simulated annealing
template <class FP, class Re>
point<FP> fermatp(polygon<FP> const &po, Re &engine, const FP begin = 1e10, const FP end = EPS, const FP delta = .999) {
  static std::uniform_real_distribution<FP> u_angle(0, 2 * PI);
  point<FP> ret = po.vs.front(), pre = po.vs.front(), now;
  FP dis_ret{}, dis_pre{}, dis_now;
  for (size_t i = 1; i < po.vs.size(); ++i) dis_pre += dist_PP(po.vs[i], ret);
  dis_ret = dis_pre;
  for (FP T = begin; T > end; T *= delta) {
    now = pre + make_P_polar(T, u_angle(engine));
    dis_now = 0;
    for (size_t i = 0; i < po.vs.size(); ++i) dis_now += dist_PP(po.vs[i], now);
    if (is_le(dis_now, dis_ret)) {
      ret = now;
      dis_ret = dis_now;
    }
    if (!is_ge(dis_now, dis_pre) || std::exp((dis_pre - dis_now) / T) > u_angle(engine) / u_angle.max()) {
      pre = now;
      dis_pre = dis_now;
    }
  }
  return ret;
}

}  // namespace tifa_libs::geo

#endif