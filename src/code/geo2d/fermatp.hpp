#ifndef TIFALIBS_GEO2D_FERMATP
#define TIFALIBS_GEO2D_FERMATP

#include "../math/kahan.hpp"
#include "../opt/heuristic_sa.hpp"
#include "make_p_polar.hpp"
#include "massp.hpp"

namespace tifa_libs::geo {

// simulated annealing
template <class FP>
point<FP> fermatp(polygon<FP> CR po, FP begin = 1e10, FP end = eps_v<FP>, FP delta = .999) {
  static rand::Gen<std::uniform_real_distribution<FP>> gen_angle(0, 2 * pi_v<FP>);
  auto gen = [](point<FP> CR pre, FP t) { return pre + make_P_polar(t, gen_angle()); };
  auto fitness = [&po](point<FP> CR p) -> FP {
    math::kahan<FP> dis = 0;
    for (u32 i = 0; i < po.size(); ++i) dis += dist_PP(po.vs[i], p);
    return dis;
  };
  opt::heuristic_sa<point<FP>, decltype(gen), decltype(fitness), FP, FP> sa(gen, fitness, begin, end, delta);
  return sa(sa(sa(massp(po)).second).second).second;
}

}  // namespace tifa_libs::geo

#endif