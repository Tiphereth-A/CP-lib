#ifndef TIFALIBS_GEO2D_CVH
#define TIFALIBS_GEO2D_CVH

#include "ins_ll.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

template <class FP>
struct cvh : public polygon<FP> {
  CEXP cvh() {}
  explicit CEXP cvh(u32 sz) : polygon<FP>(sz) {}
  explicit CEXP cvh(vec<point<FP>> CR vs_, bool inited = false, bool strict = true) : polygon<FP>(vs_) {
    if (!inited) strict ? init<true>() : init<false>();
  }

  friend std::istream &operator>>(std::istream &is, cvh &ch) {
    for (auto &i : ch.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, cvh<FP> CR ch) {
    if (ch.vs.empty()) return os;
    for (auto it = ch.vs.begin(); it != ch.vs.end() - 1; ++it) os << *it << ' ';
    return os << ch.vs.back();
  }

  template <bool strict = true>
  CEXP cvh &init() {
    this->reunique();
    const u32 n = this->size();
    if (n <= 1) return *this;
    vec<point<FP>> cvh(n * 2);
    u32 sz_cvh = 0;
    for (u32 i = 0; i < n; cvh[sz_cvh++] = this->vs[i++])
      if CEXP (strict)
        while (sz_cvh > 1 && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) <= 0) --sz_cvh;
      else
        while (sz_cvh > 1 && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) < 0) --sz_cvh;
    for (u32 i = n - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = this->vs[i--])
      if CEXP (strict)
        while (sz_cvh > t && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) <= 0) --sz_cvh;
      else
        while (sz_cvh > t && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) < 0) --sz_cvh;
    return cvh.resize(sz_cvh - 1), this->vs = cvh, *this;
  }

  CEXP FP diameter() const {
    const u32 n = this->size();
    if (n <= 1) return FP{};
    u32 is = 0, js = 0;
    flt_ (u32, k, 1, n) is = this->vs[k] < this->vs[is] ? k : is, js = this->vs[js] < this->vs[k] ? k : js;
    u32 i = is, j = js;
    FP ret = dist_PP(this->vs[i], this->vs[j]);
    do (++(((this->vs[this->next(i)] - this->vs[i]) ^ (this->vs[this->next(j)] - this->vs[j])) >= 0 ? j : i)) %= n, ret = max(ret, dist_PP(this->vs[i], this->vs[j]));
    while (i != is || j != js);
    return ret;
  }

  CEXP cvh &do_minkowski_sum_nonstrict(cvh<FP> CR r) {
    const u32 n = this->size(), m = r.size();
    if (!m) return *this;
    if (!n) return *this = r;
    vec<point<FP>> result;
    result.reserve(n + m);
    u32 midxl = 0;
    flt_ (u32, i, 1, n) midxl = this->vs[i] < this->vs[midxl] ? i : midxl;
    u32 midxr = 0;
    flt_ (u32, i, 1, m) midxr = r[i] < r[midxr] ? i : midxr;
    bool fl = false, fr = false;
    for (u32 idxl = midxl, idxr = midxr; !(idxl == midxl && fl) || !(idxr == midxr && fr);) {
      point diffl = this->vs[this->next(idxl)] - this->vs[idxl], diffr = r[r.next(idxr)] - r[idxr];
      bool f = !(idxl == midxl && fl) && ((idxr == midxr && fr) || is_pos(diffl ^ diffr));
      result.push_back(this->vs[idxl] + r[idxr] + (f ? diffl : diffr));
      (f ? idxl : idxr) = (f ? this->next(idxl) : r.next(idxr)), (f ? fl : fr) |= !(f ? idxl : idxr);
    }
    return this->vs = result, *this;
  }
  CEXP cvh &do_minkowski_sum(cvh<FP> CR r) { return do_minkowski_sum_nonstrict(r).init(); }
  CEXP cvh &do_ins_CVHhP(line<FP> CR l) {
    const u32 n = this->size();
    vec<point<FP>> cvc;
    flt_ (u32, i, 0, n) {
      point p1 = this->vs[i], p2 = this->vs[this->next(i)];
      int d1 = l.toleft(p1), d2 = l.toleft(p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, l));
    }
    return this->vs = cvc, *this;
  }
  template <class F>
  requires requires(F f, point<FP> i, point<FP> ni, point<FP> j) { f(i, ni, j); }
  CEXP void rotcaliper(F &&f) const {
    auto CR p = this->vs;
    for (u32 i = 0, j = 1; i < p.size(); ++i) {
      auto ni = this->next(i);
      f(p[i], p[ni], p[j]);
      while (!is_lt(cross(p[ni], p[this->next(j)], p[i]) - cross(p[ni], p[j], p[i]))) f(p[i], p[ni], p[j = this->next(j)]);
    }
  }
};

}  // namespace tifa_libs::geo

#endif