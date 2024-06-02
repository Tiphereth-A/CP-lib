#ifndef TIFALIBS_MATH_YOUNGT
#define TIFALIBS_MATH_YOUNGT

#include "../util/util.hpp"

namespace tifa_libs::math {

class Youngt {
  vvecu d;
  u32 n;

 public:
  CEXP explicit Youngt(vecu CR l) {
    for (auto i : l) insert(i);
  }
  CEXP Youngt(std::initializer_list<u32> l = {}) {
    for (auto i : l) insert(i);
  }
  CEXP Youngt(std::initializer_list<std::initializer_list<u32>> l) {
    for (auto&& i : l) d.emplace_back(i);
  }

  // height() == len(longest non-decresing seq.)
  CEXP u32 height() const { return (u32)d.size(); }
  // width() == len(longest incresing seq.)
  CEXP u32 width() const { return (u32)d[0].size(); }
  CEXP cT_(u32) size() const { return n; }
  CEXP vvecu& data() { return d; }
  CEXP cT_(vvecu) data() const { return d; }
  CEXP u32& operator()(u32 h, u32 w) { return d[h][w]; }
  CEXP cT_(u32) operator()(u32 h, u32 w) const { return d[h][w]; }
  CEXP u32 hook(u32 h, u32 w) const {
    assert(h < height() && w < d[h].size());
    return u32(d[h].size() - w + h);
  }
  CEXP void insert(u32 val) {
    ++n;
    for (auto& i : d) {
      auto it = std::ranges::lower_bound(i, val);
      if (it == i.end()) return i.push_back(val);
      swap(val, *it);
    }
    d.push_back({val});
  }
  friend std::ostream& operator<<(std::ostream& os, Youngt CR yt) {
    for (u32 i = 0; i < yt.height() - 1; ++i)
      flt_ (u32, j, 0, (u32)yt.d[i].size()) os << yt.d[i][j] << " \n"[j == yt.d[i].size() - 1];
    os << yt.d.back()[0];
    for (u32 j = 1; j < yt.d.back().size(); ++j) os << ' ' << yt.d.back()[j];
    return os;
  }
};

}  // namespace tifa_libs::math

#endif