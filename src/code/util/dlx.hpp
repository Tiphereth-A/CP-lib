#ifndef TIFALIBS_UTIL_DLX
#define TIFALIBS_UTIL_DLX

#include "util.hpp"

namespace tifa_libs::util {

class DLX {
  struct node {
    usz l, r, u, d, row, col;
    constexpr node(usz l = 0, usz r = 0, usz u = 0, usz d = 0, usz row = 0, usz col = 0) : l(l), r(r), u(u), d(d), row(row), col(col) {}
  };
  vec<node> data;
  vec<usz> cnt_col;
  const bool mans;

#define l_(x) data[x].l
#define r_(x) data[x].r
#define u_(x) data[x].u
#define d_(x) data[x].d
#define row_(x) data[x].row
#define col_(x) data[x].col
#define dlxfor_(i, l, dir) for (usz ied__ = (l), i = dir##_(ied__); i != ied__; i = dir##_(i))

  void remove_(usz col) {
    r_(l_(col)) = r_(col);
    l_(r_(col)) = l_(col);
    dlxfor_ (i, col, d)
      dlxfor_ (j, i, r) {
        u_(d_(j)) = u_(j);
        d_(u_(j)) = d_(j);
        --cnt_col[col_(j)];
      }
  }
  void resume_(usz col) {
    r_(l_(col)) = l_(r_(col)) = col;
    dlxfor_ (i, col, u)
      dlxfor_ (j, i, r) {
        u_(d_(j)) = d_(u_(j)) = j;
        ++cnt_col[col_(j)];
      }
  }
  template <class F>
  bool dance_(vec<usz> &ans, F cb) {
    usz now = r_(0);
    if (now == 0) return cb(ans), true;
    dlxfor_ (i, 0, r)
      if (cnt_col[i] < cnt_col[now]) now = i;
    remove_(now);
    bool ret = false;
    dlxfor_ (i, now, d) {
      ans.push_back(row_(i));
      dlxfor_ (j, i, r) remove_(col_(j));
      ret |= dance_(ans, cb);
      dlxfor_ (j, i, l) resume_(col_(j));
      if (!mans && ret) return true;
      ans.pop_back();
    }
    resume_(now);
    return ret;
  }
  void ins_row_(usz row, vec<usz> const &cols) {
    assert(row > 0);
    usz n = data.size();
    for (usz i = 0; i < cols.size(); ++i) {
      data.emplace_back(n + i - 1, n + i + 1, u_(cols[i]), cols[i], row, cols[i]);
      u_(cols[i]) = d_(u_(cols[i])) = n + i;
      ++cnt_col[cols[i]];
      if (d_(cols[i]) == cols[i]) d_(cols[i]) = n + i;
    }
    r_(l_(n) = data.size() - 1) = n;
  }

 public:
  explicit DLX(vvec<bool> const &grid, bool multi_ans = false) : data(), cnt_col(), mans(multi_ans) {
    usz col = grid[0].size();
    assert(col > 0);
    cnt_col.resize(col + 1);
    data.reserve(col + 1);
    for (usz i = 0; i <= col; ++i) data.emplace_back(i - 1, i + 1, i, i, 0, i);
    r_(l_(0) = col) = 0;
    for (usz i = 0; i < grid.size(); ++i) {
      vec<usz> _;
      _.reserve(col);
      for (usz j = 0; j < col; ++j)
        if (grid[i][j]) _.push_back(j + 1);
      _.shrink_to_fit();
      if (!_.empty()) ins_row_(i + 1, _);
    }
  }

  template <class F>
  std::optional<vec<usz>> dance(F cb) {
    vec<usz> ans;
    if (!dance_(ans, cb)) return {};
    return ans;
  }

#undef l_
#undef r_
#undef u_
#undef d_
#undef row_
#undef col_
#undef dlxfor_
};

}  // namespace tifa_libs::util

#endif