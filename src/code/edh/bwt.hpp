#ifndef TIFALIBS_EDH_BWT
#define TIFALIBS_EDH_BWT

#include "../str/suffix_array.hpp"

namespace tifa_libs {

CEXP strn bwt(strn s) {
  s += s[0];
  str::suffixarray<strn> sa(s);
  strn ret = s;
  flt_ (u32, i, 1, (u32)sa.sa.size()) ret[i - 1] = s[sa.sa[i] - 1];
  return ret.pop_back(), ret;
}

}  // namespace tifa_libs

#endif