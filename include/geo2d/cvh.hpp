#ifndef TIFALIBS_GEO2D_CVH
#define TIFALIBS_GEO2D_CVH

#include "dot.hpp"
#include "ins_ll.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

template <class FP>
struct cvh : public polygon<FP> {
  CEXP cvh() = default;
  CEXPE cvh(u32 sz) NE : polygon<FP>(sz) {}
  CEXP cvh(spn<point<FP>> vs_, bool inited = false, bool strict = true) NE : polygon<FP>(vs_) {
    if (!inited) strict ? init<true>() : init<false>();
  }

  friend auto &operator>>(istream_c auto &is, cvh &ch) NE {
    for (auto &i : ch.vs) is >> i;
    return is;
  }
  friend auto &operator<<(ostream_c auto &os, cvh<FP> CR ch) NE {
    if (ch.vs.empty()) return os;
    for (auto it = ch.vs.begin(); it != ch.vs.end() - 1; ++it) os << *it << ' ';
    return os << ch.vs.back();
  }

  template <bool strict = true>
  CEXP cvh &init() NE {
    this->reunique();
    const u32 n = this->size();
    if (n <= 2) return *this;
    vec<point<FP>> cvh(n * 2);
    u32 m = 0;
    for (u32 i = 0; i < n; cvh[m++] = (*this)[i++])
      if CEXP (strict)
        while (m > 1 && sgn_cross(cvh[m - 2], cvh[m - 1], (*this)[i]) <= 0) --m;
      else
        while (m > 1 && sgn_cross(cvh[m - 2], cvh[m - 1], (*this)[i]) < 0) --m;
    for (u32 i = n - 2, t = m; ~i; cvh[m++] = (*this)[i--])
      if CEXP (strict)
        while (m > t && sgn_cross(cvh[m - 2], cvh[m - 1], (*this)[i]) <= 0) --m;
      else
        while (m > t && sgn_cross(cvh[m - 2], cvh[m - 1], (*this)[i]) < 0) --m;
    cvh.resize(m - 1);
    u32 p = 0;
    flt_ (u32, i, 1, m - 1)
      if (cvh[i] < cvh[p]) p = i;
    rotate(cvh, cvh.begin() + p), this->vs = cvh;
    return *this;
  }
  // @return true if @p in convex hull (include border)
  CEXP bool contains(point<FP> CR p) CNE {
    auto it = lower_bound(this->vs.begin() + 1, this->vs.end(), p, [&](point<FP> CR l, point<FP> CR r) NE { return is_pos(cross((*this)[0], l, r)); }) - 1;
    auto next_it = this->next(it);
    if (auto res = sgn_cross(p, *it, *next_it); res) return ~res;
    else return !res && !is_pos(dot(p, *it, *next_it));
  }
  template <bool get_index = false>
  CEXP auto diameter() CNE {
    const u32 n = this->size();
    if (n <= 1) return std::conditional_t<get_index, edge_t<FP>, FP>{};
    u32 is = 0, js = 0;
    flt_ (u32, k, 1, n)
      if ((*this)[js] < (*this)[k]) js = k;
    u32 i = is, j = js;
    std::conditional_t<get_index, edge_t<FP>, FP> ret;
    if CEXP (get_index) ret = {dist_PP((*this)[i], (*this)[j]), i, j};
    else ret = dist_PP((*this)[i], (*this)[j]);
    do {
      (++((((*this)[this->next(i)] - (*this)[i]) ^ ((*this)[this->next(j)] - (*this)[j])) >= 0 ? j : i)) %= n;
      if CEXP (get_index) ret = max(ret, edge_t<FP>{dist_PP((*this)[i], (*this)[j]), i, j});
      else ret = max(ret, dist_PP((*this)[i], (*this)[j]));
    } while (i != is || j != js);
    return ret;
  }
  CEXP cvh &do_minkowski_sum(cvh<FP> CR r) NE {
    const u32 n = this->size(), m = r.size();
    if (!m) return *this;
    if (!n) return *this = r;
    vec<point<FP>> res{(*this)[0] + r[0]};
    res.reserve(n + m);
    u32 i = 0, j = 0;
    while (i < n && j < m) {
      auto dl = (*this)[this->next(i)] - (*this)[i], dr = r[r.next(j)] - r[j];
      bool f = !is_neg(dl ^ dr);
      res.push_back(res.back() + (f ? dl : dr)), ++(f ? i : j);
    }
    while (i < n) res.push_back(res.back() + ((*this)[this->next(i)] - (*this)[i])), ++i;
    while (j < m) res.push_back(res.back() + (r[r.next(j)] - r[j])), ++j;
    this->vs = res;
    return *this;
  }
  CEXP cvh &do_ins_CVHhP(line<FP> CR l) NE {
    const u32 n = this->size();
    vec<point<FP>> cvc;
    flt_ (u32, i, 0, n) {
      point p1 = (*this)[i], p2 = (*this)[this->next(i)];
      int d1 = l.toleft(p1), d2 = l.toleft(p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, l));
    }
    this->vs = cvc;
    return *this;
  }
};

}  // namespace tifa_libs::geo

#endif