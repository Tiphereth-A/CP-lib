#ifndef TIFA_LIBS_GEO2D_CVH
#define TIFA_LIBS_GEO2D_CVH

#include "ins_ll.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

template <class FP>
struct cvh : public polygon<FP> {
  cvh() {}
  explicit cvh(size_t sz) : polygon<FP>(sz) {}
  explicit cvh(vec<point<FP>> const &vs_, bool inited = false, bool strict = true) : polygon<FP>(vs_) {
    if (!inited) strict ? init() : init_nonstrict();
  }

  friend std::istream &operator>>(std::istream &is, cvh &ch) {
    for (auto &i : ch.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, cvh<FP> const &ch) {
    if (ch.vs.empty()) return os;
    for (auto it = ch.vs.begin(); it != ch.vs.end() - 1; ++it) os << *it << ' ';
    return os << ch.vs.back();
  }

  cvh &init() {
    size_t n = this->vs.size();
    if (n <= 1) return *this;
    this->resort();
    vec<point<FP>> cvh(n * 2);
    size_t sz_cvh = 0;
    for (size_t i = 0; i < n; cvh[sz_cvh++] = this->vs[i++])
      while (sz_cvh > 1 && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) <= 0) --sz_cvh;
    for (size_t i = n - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = this->vs[i--])
      while (sz_cvh > t && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) <= 0) --sz_cvh;
    cvh.resize(sz_cvh - 1);
    this->vs = cvh;
    return *this;
  }
  cvh &init_nonstrict() {
    this->reunique();
    size_t n = this->vs.size();
    if (n <= 1) return *this;
    vec<point<FP>> cvh(n * 2);
    size_t sz_cvh = 0;
    for (size_t i = 0; i < n; cvh[sz_cvh++] = this->vs[i++])
      while (sz_cvh > 1 && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) < 0) --sz_cvh;
    for (size_t i = n - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = this->vs[i--])
      while (sz_cvh > t && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) < 0) --sz_cvh;
    cvh.resize(sz_cvh - 1);
    this->vs = cvh;
    return *this;
  }

  FP diameter() const {
    size_t n = this->vs.size();
    if (n <= 1) return FP{};
    size_t is = 0, js = 0;
    for (size_t k = 1; k < n; ++k) {
      is = this->vs[k] < this->vs[is] ? k : is;
      js = this->vs[js] < this->vs[k] ? k : js;
    }
    size_t i = is, j = js;
    FP ret = dist_PP(this->vs[i], this->vs[j]);
    do {
      (++(((this->vs[this->next(i)] - this->vs[i]) ^ (this->vs[this->next(j)] - this->vs[j])) >= 0 ? j : i)) %= n;
      ret = std::max(ret, dist_PP(this->vs[i], this->vs[j]));
    } while (i != is || j != js);
    return ret;
  }

  cvh &do_minkowski_sum_nonstrict(cvh<FP> const &r) {
    size_t n = this->vs.size(), m = r.vs.size();
    if (!m) return *this;
    if (!n) return *this = r;
    vec<point<FP>> result;
    result.reserve(n + m);
    size_t midxl = 0;
    for (size_t i = 1; i < n; ++i) midxl = this->vs[i] < this->vs[midxl] ? i : midxl;
    size_t midxr = 0;
    for (size_t i = 1; i < m; ++i) midxr = r[i] < r[midxr] ? i : midxr;
    bool fl = false, fr = false;
    for (size_t idxl = midxl, idxr = midxr; !(idxl == midxl && fl) || !(idxr == midxr && fr);) {
      point diffl = this->vs[this->next(idxl)] - this->vs[idxl];
      point diffr = r[r.next(idxr)] - r[idxr];
      bool f = !(idxl == midxl && fl) && ((idxr == midxr && fr) || is_pos(diffl ^ diffr));
      result.push_back(this->vs[idxl] + r[idxr] + (f ? diffl : diffr));
      (f ? idxl : idxr) = (f ? this->next(idxl) : r.next(idxr));
      (f ? fl : fr) |= !(f ? idxl : idxr);
    }
    this->vs = result;
    return *this;
  }
  friend cvh minkowski_sum_nonstrict(cvh l, cvh<FP> const &r) { return l.do_minkowski_sum_nonstrict(r); }

  cvh &do_minkowski_sum(cvh<FP> const &r) { return do_minkowski_sum_nonstrict(r).init(); }
  friend cvh minkowski_sum(cvh l, cvh<FP> const &r) { return l.do_minkowski_sum(r); }

  cvh &do_ins_CVHhP(line<FP> const &l) {
    size_t n = this->vs.size();
    vec<point<FP>> cvc;
    for (size_t i = 0; i < n; ++i) {
      point p1 = this->vs[i], p2 = this->vs[this->next(i)];
      int d1 = sgn_cross(l.l, l.r, p1), d2 = sgn_cross(l.l, l.r, p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, l));
    }
    this->vs = cvc;
    return *this;
  }
  friend cvh ins_CVHhP(cvh ch, line<FP> const &l) { return ch.do_ins_CVHhP(l); }
};

}  // namespace tifa_libs::geo

#endif