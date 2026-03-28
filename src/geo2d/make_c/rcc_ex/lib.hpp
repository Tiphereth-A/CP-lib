#pragma once

#include "../../ins/cc/lib.hpp"
#include "../../rel/cc/lib.hpp"

namespace tifa_libs {

// make circle by radius and 2 external tagante circle
// maybe duplicate
template <class FP>
CEXP auto make_C_rCC_ex(FP r, circle<FP> CR c1, circle<FP> CR c2) NE {
  std::optional<ptt<circle<FP>>> ret;
  if (relation_CC(c1, c2) == RELCC::lyingin) return ret;
  auto CR ps = ins_CC<FP>({c1.o, c1.r + r}, {c2.o, c2.r + r});
  if (!ps) return ret;
  ret.emplace(circle{ps->first, r}, circle{ps->second, r});
  return ret;
}

}  // namespace tifa_libs
