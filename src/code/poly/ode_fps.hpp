#ifndef TIFALIBS_POLY_ODE_FPS
#define TIFALIBS_POLY_ODE_FPS

#include "exp_fps.hpp"
#include "int_fps.hpp"
#include "inv_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore, class G, class DG>
requires requires(poly<mint, ccore> f, size_t n, G g, DG dg) {
  { g(f, n) } -> std::same_as<poly<mint, ccore>>;
  { dg(f, n) } -> std::same_as<poly<mint, ccore>>;
}
constexpr poly<mint, ccore> ode_fps(G&& g, DG&& dg, mint a, u32 n) {
  poly<mint, ccore> f{a};
  for (u32 i = 1; i < n; i *= 2) {
    poly<mint, ccore> r = exp_fps(int_fps(-dg(f, i * 2))),
                      h = int_fps(((g(f, i * 2) - (dg(f, i * 2) * f).pre(i * 2)) * r).pre(i * 2));
    f = ((h + a) * inv_fps(r, i * 2)).pre(i * 2);
  }
  return f.pre(n);
}

}  // namespace tifa_libs::math

#endif