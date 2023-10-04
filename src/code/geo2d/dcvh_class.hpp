#ifndef TIFA_LIBS_GEO2D_DCVH_CLASS
#define TIFA_LIBS_GEO2D_DCVH_CLASS

#include "cvh_class.hpp"
#include "util.hpp"

namespace tifa_libs::geo2d {

// Dynamic Convex Hull
template <class FP>
class dcvh {
protected:
  // Dynamic half Convex Hull
  struct DHCVH {
    int sgn_ = 1;
    std::set<point<FP>> vs;

    DHCVH() {}
    explicit DHCVH(int sgn_):
      sgn_(sgn_) {}

    bool contains(point<FP> const &p) const {
      auto it = vs.lower_bound({p.x, -std::numeric_limits<FP>::max()});
      if (it == vs.end()) return false;
      if (it->x == p.x) return sgn(p.y - it->y) * sgn_ <= 0;
      if (it == vs.begin()) return false;
      auto j = it;
      return sgn_cross(*(--j), *it, p) * sgn_ <= 0;
    }
    bool erase(typename std::set<point<FP>>::const_iterator it) {
      if (it == vs.begin()) return false;
      auto j = it, k = it;
      if (++k == vs.end()) return false;
      return sgn_cross(*(--j), *it, *k) * sgn_ >= 0 ? vs.erase(it), true : false;
    }
    DHCVH &insert(point<FP> const &p) {
      if (contains(p)) return *this;
      auto tmp = vs.lower_bound({p.x, -std::numeric_limits<FP>::max()});
      if (tmp != vs.end() && tmp->x == p.x) vs.erase(tmp);
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
  dcvh() {}

  bool contains(point<FP> const &p) const { return hcvh_up.contains(p) && hcvh_down.contains(p); }
  dcvh &insert(point<FP> const &p) {
    hcvh_up.insert(p);
    hcvh_down.insert(p);
    return *this;
  }
  cvh<FP> to_CVH() const {
    cvh<FP> ret;
    for (auto it = hcvh_up.vs.begin(); it != hcvh_up.vs.end(); ++it) ret.vs.push_back(*it);
    for (auto it = hcvh_down.vs.begin(); it != hcvh_down.vs.end(); ++it) ret.vs.push_back(*it);
    ret.resort_in_counterclockwise();
    return ret;
  }
};

}  // namespace tifa_libs::geo2d

#endif