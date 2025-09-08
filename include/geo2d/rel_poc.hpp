#ifndef TIFALIBS_GEO2D_REL_POC
#define TIFALIBS_GEO2D_REL_POC

#include "circle.hpp"
#include "polygon.hpp"
#include "rel_cs.hpp"
#include "rel_pop.hpp"

namespace tifa_libs::geo {

// relation between polygon/convex hull and circle
// clang-format off
enum class RELPoC : u8 { otherwise, touchin, covered };
// clang-format on

template <class FP>
CEXP RELPoC relation_PoC(polygon<FP> CR po, circle<FP> CR c) NE {
  auto x = RELPoC::covered;
  if (relation_PoP(po, c.o) != RELPoP::inside) return RELPoC::otherwise;
  flt_ (u32, i, 0, po.size())
    if (auto _ = relation_CS(c, {po.vs[i], po.vs[po.next(i)]}); _ == RELCS::intersect) return RELPoC::otherwise;
    else if (_ == RELCS::tagante) x = RELPoC::touchin;
  return x;
}

}  // namespace tifa_libs::geo

#endif