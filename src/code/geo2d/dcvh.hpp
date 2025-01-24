#ifndef TIFALIBS_GEO2D_DCVH
#define TIFALIBS_GEO2D_DCVH

#include "argsort.hpp"
#include "cvh.hpp"

namespace tifa_libs::geo {

// Dynamic Convex Hull
template <class FP>
class dcvh {
  // Dynamic half Convex Hull
  struct DHCVH {
    const int sgn_;
    set<point<FP>> vs;

    CEXPE DHCVH(int sgn_ = 1) NE : sgn_(sgn_) {}

    CEXP bool contains(point<FP> CR p) CNE {
      auto it = vs.lower_bound(point<FP>{p.x, -std::numeric_limits<FP>::max()});
      if (it == vs.end()) return false;
      if (it->x == p.x) return sgn(p.y - it->y) * sgn_ <= 0;
      if (it == vs.begin()) return false;
      auto j = it;
      return sgn_cross(*(--j), *it, p) * sgn_ <= 0;
    }
    template <class IT>
    CEXP bool erase(IT it) NE {
      if (it == vs.begin()) return false;
      auto j = it, k = it;
      if (++k == vs.end()) return false;
      bool _ = sgn_cross(*(--j), *it, *k) * sgn_ >= 0;
      if (_) vs.erase(it);
      return _;
    }
    CEXP DHCVH &insert(point<FP> CR p) NE {
      if (contains(p)) return *this;
      auto _ = vs.lower_bound(point<FP>{p.x, -std::numeric_limits<FP>::max()});
      if (_ != vs.end() && _->x == p.x) vs.erase(_);
      vs.insert(p);
      auto i = vs.find(p), j = i;
      if (i != vs.begin()) {
        --j;
        while (erase(j++)) --j;
      }
      if (++j != vs.end())
        while (erase(j--)) ++j;
      return *this;
    }
  } hcvh_up{1}, hcvh_down{-1};

 public:
  CEXP dcvh() = default;

  CEXP bool contains(point<FP> CR p) CNE { return hcvh_up.contains(p) && hcvh_down.contains(p); }
  CEXP dcvh &insert(point<FP> CR p) NE {
    hcvh_up.insert(p), hcvh_down.insert(p);
    return *this;
  }
  CEXP cvh<FP> to_CVH() CNE {
    cvh<FP> ret;
    std::ranges::copy(hcvh_up.vs, ret.vs.begin());
    std::ranges::copy(hcvh_down.vs, std::back_inserter(ret.vs));
    argsort(ret.vs);
    return ret;
  }
};

}  // namespace tifa_libs::geo

#endif