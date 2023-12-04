#ifndef TIFALIBS_GEO2D_REL_POC
#define TIFALIBS_GEO2D_REL_POC

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
RELPoC relation_PoC(polygon<FP> const &po, circle<FP> const &c) {
  auto x = covered_poc;
  if (relation_PoP(po, c.o) != RELPoP::inside_pop) return otherwise_poc;
  for (u32 i = 0; i < (u32)po.vs.size(); ++i) {
    RELCS state = relation_CS(c, {po.vs[i], po.vs[po.next(i)]});
    if (state == RELCS::intersect_cs) return otherwise_poc;
    if (state == RELCS::tagante_cs) x = touchin_poc;
  }
  return x;
}

}  // namespace tifa_libs::geo

#endif