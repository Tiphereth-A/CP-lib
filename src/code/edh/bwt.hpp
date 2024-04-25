#ifndef TIFALIBS_EDH_BWT
#define TIFALIBS_EDH_BWT

#include "../str/suffix_array.hpp"

namespace tifa_libs {

CEXP strn bwt(strn s) {
  s += s[0];
  str::suffixarray<strn> sa(s);
  strn ret = s;
  for (u32 i = 1; i < sa.sa.size(); ++i) ret[i - 1] = s[sa.sa[i] - 1];
  ret.pop_back();
  return ret;
}

}  // namespace tifa_libs

#endif