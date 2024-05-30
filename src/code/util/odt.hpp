#ifndef TIFALIBS_UTIL_ODT
#define TIFALIBS_UTIL_ODT

#include "util.hpp"

namespace tifa_libs {

template <class T>
class ODT {
  //! [l, r]
  struct TIFA {
    u32 l, r;
    mutable T v;
    //! [l, r]
    CEXP TIFA(u32 l, u32 r, cT_(T) v) : l(l), r(r), v(v) {}
    CEXP auto operator<=>(TIFA CR o) const { return (i32)l - (i32)o.l; }
  };

  std::set<TIFA> data;

 public:
  explicit CEXP ODT() : data() {}
  explicit CEXP ODT(vec<T> CR c) : ODT() {
    u32 cnt = 0;
    for (auto &&i : c) data.emplace(cnt, cnt, i), ++cnt;
  }

  CEXP void clear() { data.clear(); }
  //! [l, r]
  CEXP void insert(u32 l, u32 r, cT_(T) v) { data.emplace(l, r, v); }
  CEXP auto find(u32 x) const { return std::prev(data.upper_bound(TIFA{x, 0, 0})); }
  CEXP auto split(u32 x) {
    auto it = find(x);
    if (it->l == x) return it;
    auto [l, r, v] = *it;
    data.erase(it), data.emplace(l, x - 1, v);
    return data.emplace(x, r, v).first;
  }
  //! [l, r]
  CEXP void assign(u32 l, u32 r, cT_(T) v) {
    auto itr = split(r + 1), itl = split(l);
    data.erase(itl, itr), data.emplace(l, r, v);
  }
  //! [l, r]
  // merge adjacent nodes with same value
  CEXP void assign_merge(u32 l, u32 r, cT_(T) v) {
    auto itl = find(l), itr = find(r);
    if (itr != data.end()) {
      if (itr != std::prev(data.end()) && itr->r == r && (++itr)->v == v) r = (itr++)->r;
      else if (itr->v != v) itr = split(r + 1), itl = find(l);
      else r = (itr++)->r;
    }
    if (itl != data.begin() && itr->l == l && std::prev(itl)->v == v) l = (--itl)->l;
    else if (itl->v != v) itl = split(l);
    else l = itl->l;
    data.erase(itl, itr), data.emplace(l, r, v);
  }
  //! [l, r]
  // @param f: (iter) -> void
  template <class F>
  CEXP void run(u32 l, u32 r, F f) {
    for (auto itr = split(r + 1), itl = split(l); itl != itr; ++itl) f(itl);
  }
  //! [l, r]
  // @param f: (iter_l, iter_r) -> auto
  template <class F>
  CEXP auto run_no_split(u32 l, u32 r, F f) const { return f(find(l), find(r)); }
};

}  // namespace tifa_libs

#endif