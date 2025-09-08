#ifndef TIFALIBS_MATH_YOUNGT
#define TIFALIBS_MATH_YOUNGT

#include "../util/alias_others.hpp"

namespace tifa_libs::math {

class Youngt {
  vvecu d;
  u32 n;

 public:
  CEXPE Youngt(spnu l) NE {
    for (auto i : l) insert(i);
  }
  CEXP Youngt(itlu l = {}) NE {
    for (auto i : l) insert(i);
  }
  CEXP Youngt(itl<itlu> l) NE {
    for (auto&& i : l) d.emplace_back(i);
  }

  // height() == len(longest non-decresing seq.)
  CEXP u32 height() CNE { return (u32)d.size(); }
  // width() == len(longest incresing seq.)
  CEXP u32 width() CNE { return (u32)d[0].size(); }
  CEXP u32 CR size() CNE { return n; }
  CEXP vvecu& data() NE { return d; }
  CEXP vvecu CR data() CNE { return d; }
  CEXP u32& operator()(u32 h, u32 w) NE { return d[h][w]; }
  CEXP u32 CR operator()(u32 h, u32 w) CNE { return d[h][w]; }
  CEXP u32 hook(u32 h, u32 w) CNE {
    assert(h < height() && w < d[h].size());
    return u32(d[h].size() - w + h);
  }
  CEXP void insert(u32 val) NE {
    ++n;
    for (auto& i : d) {
      auto it = lower_bound(i, val);
      if (it == end(i)) return i.push_back(val);
      swap(val, *it);
    }
    d.push_back({val});
  }
  friend std::ostream& operator<<(std::ostream& os, Youngt CR yt) NE {
    for (u32 i = 0; i < yt.height() - 1; ++i)
      flt_ (u32, j, 0, (u32)yt.d[i].size()) os << yt.d[i][j] << " \n"[j == yt.d[i].size() - 1];
    os << yt.d.back()[0];
    for (u32 j = 1; j < yt.d.back().size(); ++j) os << ' ' << yt.d.back()[j];
    return os;
  }
};

}  // namespace tifa_libs::math

#endif