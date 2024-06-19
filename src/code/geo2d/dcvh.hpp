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
    std::set<point<FP>> vs;

    CEXPE DHCVH(int sgn_ = 1) : sgn_(sgn_) {}

    CEXP bool contains(point<FP> CR p) const {
      auto it = vs.lower_bound(point<FP>{p.x, -std::numeric_limits<FP>::max()});
      if (it == vs.end()) return false;
      if (it->x == p.x) return sgn(p.y - it->y) * sgn_ <= 0;
      if (it == vs.begin()) return false;
      auto j = it;
      return sgn_cross(*(--j), *it, p) * sgn_ <= 0;
    }
    CEXP bool erase(TPN std::set<point<FP>>::const_iterator it) {
      if (it == vs.begin()) return false;
      auto j = it, k = it;
      if (++k == vs.end()) return false;
      return sgn_cross(*(--j), *it, *k) * sgn_ >= 0 ? vs.erase(it), true : false;
    }
    CEXP DHCVH &insert(point<FP> CR p) {
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
  CEXP dcvh() {}

  CEXP bool contains(point<FP> CR p) const { return hcvh_up.contains(p) && hcvh_down.contains(p); }
  CEXP dcvh &insert(point<FP> CR p) { return hcvh_up.insert(p), hcvh_down.insert(p), *this; }
  CEXP cvh<FP> to_CVH() const {
    cvh<FP> ret;
    return std::ranges::copy(hcvh_up.vs, ret.vs.begin()), std::ranges::copy(hcvh_down.vs, std::back_inserter(ret.vs)), argsort(ret.vs), ret;
  }
};

}  // namespace tifa_libs::geo

#endif