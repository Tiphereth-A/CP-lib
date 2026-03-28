#pragma once

#include "../deriv/lib.hpp"
#include "../int/lib.hpp"
#include "../inv/lib.hpp"

namespace tifa_libs {

CEXP auto ln_fps(poly_c auto p, u32 n = 0) NE {
  if (assert(p[0] == 1); !n) n = (u32)p.size();
  auto _ = deriv_fps(p).pre(n);
  _.conv(inv_fps(p, n));
  return int_fps(_).pre(n);
}

}  // namespace tifa_libs
