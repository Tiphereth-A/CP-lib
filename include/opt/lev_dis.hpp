#ifndef TIFALIBS_OPT_LEV_DIS
#define TIFALIBS_OPT_LEV_DIS

#include "../util/alias_others.hpp"

namespace tifa_libs::opt {

//@return ans[i][j] = lev(a[0..i), b[0..j))
template <common_range T>
CEXP vvecu lev_dis(T CR a, T CR b) NE {
  const u32 n = (u32)a.size(), m = (u32)b.size();
  vvecu ans(n + 1, vecu(m + 1));
  flt_ (u32, i, 0, n + 1) ans[i][0] = i;
  flt_ (u32, i, 0, m + 1) ans[0][i] = i;
  flt_ (u32, i, 1, n + 1)
    flt_ (u32, j, 1, m + 1) ans[i][j] = min({ans[i - 1][j - 1] + !(a[i - 1] == b[j - 1]), ans[i][j - 1] + 1, ans[i - 1][j] + 1});
  return ans;
}

}  // namespace tifa_libs::opt

#endif