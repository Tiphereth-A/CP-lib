#ifndef TIFALIBS_GEO2D_REL_POC
#define TIFALIBS_GEO2D_REL_POC

#include "circle.hpp"
#include "polygon.hpp"
#include "rel_cs.hpp"
#include "rel_pop.hpp"

namespace tifa_libs::geo {

// relation between polygon/convex hull and circle
enum RELPoC { otherwise_poc,
              touchin_poc,
              covered_poc };

template <class FP>
CEXP RELPoC relation_PoC(polygon<FP> CR po, circle<FP> CR c) NE {
  auto x = covered_poc;
  if (relation_PoP(po, c.o) != inside_pop) return otherwise_poc;
  flt_ (u32, i, 0, po.size())
    if (auto _ = relation_CS(c, {po.vs[i], po.vs[po.next(i)]}); _ == intersect_cs) return otherwise_poc;
    else if (_ == tagante_cs) x = touchin_poc;
  return x;
}

}  // namespace tifa_libs::geo

#endif