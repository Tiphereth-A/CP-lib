#ifndef TIFALIBS_DS_DSU_DELINEATION
#define TIFALIBS_DS_DSU_DELINEATION

#include "../util/traits.hpp"

namespace tifa_libs::ds {

CEXP vvecu dsu_delineation(dsu_c auto& dsu) NE {
  const u32 n = dsu.size();
  vvecu mp(n);
  flt_ (u32, u, 0, n) mp[(u32)dsu.find(u)].push_back(u);
  auto [l, r] = remove_if(mp, [](auto CR x) { return x.empty(); });
  mp.erase(l, r);
  return mp;
}

}  // namespace tifa_libs::ds

#endif