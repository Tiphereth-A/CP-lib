#ifndef TIFALIBS_OPT_HEURISTIC_SA
#define TIFALIBS_OPT_HEURISTIC_SA

#include "../rand/gen.hpp"

namespace tifa_libs::opt {

template <class T, class Fg, class Ff, class Ft = f64, class Tt = f64>
requires requires(Ff fit, Fg gen, cT_(T) sample, Tt t) {
  { fit(sample) } -> std::same_as<Ft>;
  { gen(sample, t) } -> std::same_as<T>;
}
class heuristic_sa {
  Fg gen;
  Ff f;
  const Tt Tmax, Tmin, dT;
  rand::Gen<Tt> g;

 public:
  // Find minimum argument of f(x)
  CEXP heuristic_sa(Fg gen, Ff f, Tt Tmax = 1e10, Tt Tmin = 1e-10, Tt dT = 1 - 1e-5) : gen(gen), f(f), Tmax(Tmax), Tmin(Tmin), dT(dT), g(0, 1) {}

  std::pair<Ft, T> operator()(T init_val) {
    T ans = init_val, now = ans;
    Ft ans_f = f(ans);
    for (Tt t = Tmax; t > Tmin; t *= dT)
      if (Ft now_f = f(now = gen(ans, t)); now_f <= ans_f || std::exp((ans_f - now_f) / t) > g.next()) ans_f = now_f, ans = now;
    return {ans_f, ans};
  }
};

}  // namespace tifa_libs::opt

#endif