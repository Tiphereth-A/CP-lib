#ifndef TIFALIBS_MATH_TRYGUB
#define TIFALIBS_MATH_TRYGUB

#include "../util/util.hpp"

namespace tifa_libs::math {

template <int B = 1 << 30>
class trygub_num {
  std::map<int, i64> d;

 public:
  void add(i64 x, int y) NE {
    d[y] += x;
    auto it = d.find(y);
    while (1) {
      i64 t = it->second / B;
      if (!t) break;
      it->second %= B, d.insert(it, {++y, 0});
      (!it->second ? it = d.erase(it) : ++it)->second += t;
    }
    if (!it->second) d.erase(it);
  }
  i64 get(int k) NE {
    auto it = d.lower_bound(k);
    i64 res = (it != d.end() && it->first == k ? it->second : 0);
    return (res - (it != d.begin() && prev(it)->second < 0) + B) % B;
  }
};

}  // namespace tifa_libs::math

#endif