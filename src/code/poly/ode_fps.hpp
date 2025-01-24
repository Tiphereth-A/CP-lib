#ifndef TIFALIBS_POLY_ODE_FPS
#define TIFALIBS_POLY_ODE_FPS

#include "exp_fps.hpp"
#include "int_fps.hpp"
#include "inv_fps.hpp"

namespace tifa_libs::math {

template <class poly, class G, class DG>
requires requires(poly f, size_t n, G g, DG dg) {
  { g(f, n) } -> std::same_as<poly>;
  { dg(f, n) } -> std::same_as<poly>;
}
CEXP auto ode_fps(G&& g, DG&& dg, TPN poly::val_t a, u32 n) NE {
  poly f{a};
  for (u32 i = 1; i < n; i *= 2) {
    auto r = exp_fps(int_fps(-dg(f, i * 2))), h = int_fps(((g(f, i * 2) - (dg(f, i * 2) * f).pre(i * 2)) * r).pre(i * 2));
    f = ((h + a) * inv_fps(r, i * 2)).pre(i * 2);
  }
  return f.pre(n);
}

}  // namespace tifa_libs::math

#endif