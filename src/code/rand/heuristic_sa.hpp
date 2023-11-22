#ifndef TIFA_LIBS_UTIL_HEURISTIC_SA
#define TIFA_LIBS_UTIL_HEURISTIC_SA

#include "gen.hpp"

namespace tifa_libs::rand {

template <class T, class Ft = f64, class Tt = f64>
class heuristic_sa {
  const Tt Tmax, Tmin, dT;
  Gen<std::uniform_real_distribution<Tt>> g;

  //? Metropolis acceptance criteria
  bool chk(Ft dfit, Tt now_T) { return dfit <= 0 || std::exp(-dfit / now_T) > g(); }

 public:
  explicit heuristic_sa(Tt Tmax = 1e10, Tt Tmin = 1e-10, Tt dT = 1 - 1e-5) : Tmax(Tmax), Tmin(Tmin), dT(dT), g(0, 1) {}

  // Find minimum argument of f(x)
  // Fg: T(T const &, Tt)
  // Ff: Ft(T const &)
  template <class Fg, class Ff>
  std::pair<Ft, T> operator()(T init_val, Fg gen, Ff f) {
    T ans = init_val, now = ans;
    Ft ans_f = f(ans);
    for (Tt t = Tmax; t > Tmin; t *= dT) {
      now = gen(ans, t);
      if (Ft now_f = f(now); chk(now_f - ans_f, t)) {
        ans = now_f;
        ans = now;
      }
    }
    return {ans_f, ans};
  }
};

}  // namespace tifa_libs::rand

#endif