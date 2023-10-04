#ifndef TIFA_LIBS_GEO2D_REL_POC
#define TIFA_LIBS_GEO2D_REL_POC

#include "circle_class.hpp"
#include "polygon_class.hpp"

#include "rel_cs.hpp"
#include "rel_pop.hpp"

namespace tifa_libs::geo2d {

// relation between polygon/convex hull and circle
enum RELA_PoC {
  otherwise_poc,
  touchin_poc,
  covered_poc
};

template <class FP>
RELA_PoC relation_PoC(polygon<FP> const &poly, circle<FP> const &c) {
  auto x = RELA_PoC::covered_poc;
  if (relation_PoP(poly, c.o) != RELA_PoP::inside_pop) return RELA_PoC::otherwise_poc;
  for (size_t i = 0; i < poly.vs.size(); ++i) {
    size_t state = relation_CS(c, {poly.vs[i], poly.vs[poly.next(i)]});
    if (state == RELA_CS::intersect_cs) return RELA_PoC::otherwise_poc;
    if (state == RELA_CS::tagante_cs) x = RELA_PoC::touchin_poc;
  }
  return x;
}

}  // namespace tifa_libs::geo2d

#endif