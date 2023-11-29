#ifndef TIFA_LIBS_GEO2D_POLY_FERMATP
#define TIFA_LIBS_GEO2D_POLY_FERMATP

#include "../rand/heuristic_sa.hpp"
#include "make_p_polar.hpp"
#include "poly_massp.hpp"

namespace tifa_libs::geo {

// simulated annealing
template <class FP>
point<FP> fermatp(polygon<FP> const &po, FP begin = 1e10, FP end = EPS<FP>, FP delta = .999) {
  static rand::Gen<std::uniform_real_distribution<FP>> gen_angle(0, 2 * PI<FP>);
  auto gen = [](point<FP> const &pre, FP t) { return pre + make_P_polar(t, gen_angle()); };
  auto fitness = [&po](point<FP> const &p) {
    FP dis = 0;
    for (u32 i = 0; i < po.vs.size(); ++i) dis += dist_PP(po.vs[i], p);
    return dis;
  };
  rand::heuristic_sa<point<FP>, decltype(gen), decltype(fitness), FP, FP> sa(gen, fitness, begin, end, delta);
  return sa(sa(sa(poly_massp(po)).second).second).second;
}

}  // namespace tifa_libs::geo

#endif