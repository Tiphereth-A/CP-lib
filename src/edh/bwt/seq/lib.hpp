#pragma once

#include "../../../str/suffix_array/lib.hpp"

namespace tifa_libs {

CEXP strn bwt(strn s) NE {
  s += s[0];
  str::suffix_array<strn> sa(s);
  strn ret = s;
  flt_ (u32, i, 1, (u32)sa.sa.size()) ret[i - 1] = s[sa.sa[i] - 1];
  ret.pop_back();
  return ret;
}

}  // namespace tifa_libs
