#ifndef TIFALIBS_OPT_DLX
#define TIFALIBS_OPT_DLX

#include "../util/alias_others.hpp"

namespace tifa_libs::opt {

class DLX {
  struct node {
    u32 l, r, u, d, row, col;
    CEXP node(u32 l = 0, u32 r = 0, u32 u = 0, u32 d = 0, u32 row = 0, u32 col = 0) NE : l(l), r(r), u(u), d(d), row(row), col(col) {}
  };
  vec<node> data;
  vecu cnt_col;
  const bool mans;

#define l_(x) data[x].l
#define r_(x) data[x].r
#define u_(x) data[x].u
#define d_(x) data[x].d
#define row_(x) data[x].row
#define col_(x) data[x].col
#define dlxfor_(i, l, dir) for (u32 ied__ = (l), i = dir##_(ied__); i != ied__; i = dir##_(i))

  CEXP void remove_(u32 col) NE {
    r_(l_(col)) = r_(col), l_(r_(col)) = l_(col);
    dlxfor_ (i, col, d)
      dlxfor_ (j, i, r) u_(d_(j)) = u_(j), d_(u_(j)) = d_(j), --cnt_col[col_(j)];
  }
  CEXP void resume_(u32 col) NE {
    r_(l_(col)) = l_(r_(col)) = col;
    dlxfor_ (i, col, u)
      dlxfor_ (j, i, r) u_(d_(j)) = d_(u_(j)) = j, ++cnt_col[col_(j)];
  }
  template <class F>
  CEXP bool dance_(vecu &ans, F &&cb) NE {
    u32 now = r_(0);
    if (now == 0) {
      cb(ans);
      return true;
    }
    dlxfor_ (i, 0, r)
      if (cnt_col[i] < cnt_col[now]) now = i;
    remove_(now);
    bool ret = false;
    dlxfor_ (i, now, d) {
      ans.push_back(row_(i));
      dlxfor_ (j, i, r) remove_(col_(j));
      ret |= dance_(ans, std::forward<F>(cb));
      dlxfor_ (j, i, l) resume_(col_(j));
      if (!mans && ret) return true;
      ans.pop_back();
    }
    resume_(now);
    return ret;
  }
  CEXP void ins_row_(u32 row, spnu cols) NE {
    assert(row > 0);
    u32 n = (u32)data.size();
    flt_ (u32, i, 0, (u32)cols.size()) {
      data.emplace_back(n + i - 1, n + i + 1, u_(cols[i]), cols[i], row, cols[i]);
      u_(cols[i]) = d_(u_(cols[i])) = n + i;
      ++cnt_col[cols[i]];
      if (d_(cols[i]) == cols[i]) d_(cols[i]) = n + i;
    }
    r_(l_(n) = u32(data.size() - 1)) = n;
  }

 public:
  CEXPE DLX(cT_(vvecb) grid, bool multi_ans = false) NE : data(), cnt_col(), mans(multi_ans) {
    u32 col = (u32)grid[0].size();
    assert(col > 0), cnt_col.resize(col + 1), data.reserve(col + 1);
    flt_ (u32, i, 0, col + 1) data.emplace_back(i - 1, i + 1, i, i, 0, i);
    r_(l_(0) = col) = 0;
    flt_ (u32, i, 0, (u32)grid.size()) {
      vecu _;
      _.reserve(col);
      flt_ (u32, j, 0, col)
        if (grid[i][j]) _.push_back(j + 1);
      if (_.shrink_to_fit(); !_.empty()) ins_row_(i + 1, _);
    }
  }
  template <class F>
  requires requires(F f, vecu sol) { f(sol); }
  CEXP std::optional<vecu> dance(F &&cb) NE {
    vecu ans;
    if (!dance_(ans, std::forward<F>(cb))) return {};
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

}  // namespace tifa_libs::opt

#endif