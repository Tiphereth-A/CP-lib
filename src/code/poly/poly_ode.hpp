#ifndef TIFALIBS_POLY_POLY_ODE
#define TIFALIBS_POLY_POLY_ODE

#include "poly_exp.hpp"
#include "poly_int.hpp"
#include "poly_inv.hpp"

namespace tifa_libs::math {

template <class poly, class G, class DG>
requires requires(poly f, size_t n, G g, DG dg) {
  { g(f, n) } -> std::same_as<poly>;
  { dg(f, n) } -> std::same_as<poly>;
}
constexpr poly poly_ode(G g, DG dg, typename poly::value_type a, u32 n) {
  poly f{a};
  for (u32 i = 1; i < n; i *= 2) {
    poly r = poly_exp(poly_int(-dg(f, i * 2))), h = poly_int(((g(f, i * 2) - (dg(f, i * 2) * f).pre(i * 2)) * r).pre(i * 2));
    f = ((h + a) * poly_inv(r, i * 2)).pre(i * 2);
  }
  return f.pre(n);
}

}  // namespace tifa_libs::math

#endif