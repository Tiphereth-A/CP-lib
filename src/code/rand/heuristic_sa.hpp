#ifndef TIFA_LIBS_UTIL_HEURISTIC_SA
#define TIFA_LIBS_UTIL_HEURISTIC_SA

#include "gen.hpp"

namespace tifa_libs::rand {

// Fg: T(T const &, Tt)
// Ff: Ft(T const &)
template <class T, class Fg, class Ff, class Ft = f64, class Tt = f64>
class heuristic_sa {
  Fg gen;
  Ff f;
  const Tt Tmax, Tmin, dT;
  Gen<std::uniform_real_distribution<Tt>> g;

 public:
  // Find minimum argument of f(x)
  explicit heuristic_sa(Fg gen, Ff f, Tt Tmax = 1e10, Tt Tmin = 1e-10, Tt dT = 1 - 1e-5) : gen(gen), f(f), Tmax(Tmax), Tmin(Tmin), dT(dT), g(0, 1) {}

  std::pair<Ft, T> operator()(T init_val) {
    T ans = init_val, now = ans;
    Ft ans_f = f(ans);
    for (Tt t = Tmax; t > Tmin; t *= dT) {
      now = gen(ans, t);
      if (Ft now_f = f(now); now_f <= ans_f || std::exp((ans_f - now_f) / t) > g()) {
        ans_f = now_f;
        ans = now;
      }
    }
    return {ans_f, ans};
  }
};

}  // namespace tifa_libs::rand

#endif