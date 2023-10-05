#ifndef TIFA_LIBS_GEO2D_REL_POC
#define TIFA_LIBS_GEO2D_REL_POC

#include "circle.hpp"
#include "polygon.hpp"
#include "rel_cs.hpp"
#include "rel_pop.hpp"

namespace tifa_libs::geo {

// relation between polygon/convex hull and circle
enum RELPoC {
  otherwise_poc,
  touchin_poc,
  covered_poc
};

template <class FP>
RELPoC relation_PoC(polygon<FP> const &poly, circle<FP> const &c) {
  auto x = RELPoC::covered_poc;
  if (relation_PoP(poly, c.o) != RELPoP::inside_pop) return RELPoC::otherwise_poc;
  for (size_t i = 0; i < poly.vs.size(); ++i) {
    size_t state = relation_CS(c, {poly.vs[i], poly.vs[poly.next(i)]});
    if (state == RELCS::intersect_cs) return RELPoC::otherwise_poc;
    if (state == RELCS::tagante_cs) x = RELPoC::touchin_poc;
  }
  return x;
}

}  // namespace tifa_libs::geo

#endif