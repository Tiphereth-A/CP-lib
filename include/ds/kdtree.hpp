#ifndef TIFALIBS_DS_KDTREE
#define TIFALIBS_DS_KDTREE

#include "../util/alias_others.hpp"
#include "../util/traits_math.hpp"
#include "bt_trv.hpp"

namespace tifa_libs::ds {

template <class T, auto op, arithm_c Coord = i32, u32 K = 2, bool remove_empty_node = false>
class KDtree {
  static_assert(K);
  struct TIFA;

 public:
  using point = arr<Coord, K>;

 private:
  using pointer = TIFA*;
  using const_pointer = const TIFA*;
  struct TIFA {
    pointer ch[2];
    T sum, val;
    point min, max, coord;
    template <u32 k>
    requires /**/ (k < K)
    static CEXP bool cmp(const_pointer l, const_pointer r) { return l->coord[k] < r->coord[k]; }
  };

  const T E;
  const u32 B;
  u32 cnt;

  CEXP pointer newnode(cT_(point) p, cT_(T) val) {
    pointer x = alloc.allocate(1);
    x->ch[0] = x->ch[1] = nullptr, x->sum = x->val = val;
    flt_ (u32, i, 0, K) x->min[i] = x->max[i] = x->coord[i] = p[i];
    return x;
  }
  CEXP void pushup(pointer x) NE {
    auto [l, r] = x->ch;
    x->sum = x->val;
    if (l) {
      x->sum = op(x->sum, l->sum);
      flt_ (u32, i, 0, K) x->max[i] = max(l->max[i], x->max[i]);
      flt_ (u32, i, 0, K) x->min[i] = min(l->min[i], x->min[i]);
    }
    if (r) {
      x->sum = op(x->sum, r->sum);
      flt_ (u32, i, 0, K) x->max[i] = max(r->max[i], x->max[i]);
      flt_ (u32, i, 0, K) x->min[i] = min(r->min[i], x->min[i]);
    }
  }

  template <u32 k>
  requires /**/ (k < K)
  CEXP void build(pointer& x, vec<pointer>& h, u32 l, u32 r) NE {
    if (l >= r) return;
    u32 mid = l + (r - l) / 2;
    nth_element(h.begin() + l, h.begin() + mid, h.begin() + r, TIFA::template cmp<k>);
    x = h[mid], x->sum = x->val;
    flt_ (u32, i, 0, K) x->min[i] = x->max[i] = x->coord[i];
    build<(k + 1) % K>(x->ch[0], h, l, mid), build<(k + 1) % K>(x->ch[1], h, mid + 1, r);
    pushup(x);
  }
  CEXP void rebuild(pointer& x) NE {
    vec<pointer> h;
    auto flatten = [&](auto&& f, pointer& x) -> void {
      if (!x) return;
      if CEXP (remove_empty_node) {
        auto _ = x->val == E;
        if (!_) h.push_back(x);
        f(f, x->ch[0]), f(f, x->ch[1]);
        if (_) alloc.deallocate(x, 1);
      } else h.push_back(x), f(f, x->ch[0]), f(f, x->ch[1]);
      x = nullptr;
    };
    flatten(flatten, x), build<0>(x, h, 0, (u32)h.size());
  }

  template <bool use_set, u32 k>
  requires /**/ (k < K)
  CEXP bool ins_set_(pointer& x, cT_(point) p, cT_(T) val) NE {
    if (!x) {
      x = newnode(p, val);
      return true;
    }
    bool f;
    if (p == x->coord) {
      f = false;
      if CEXP (!use_set) x->val = op(x->val, val), x->sum = op(x->sum, val);
      else {
        x->val = val, x->sum = val;
        if (x->ch[0]) x->sum = op(x->sum, x->ch[0]->sum);
        if (x->ch[1]) x->sum = op(x->sum, x->ch[1]->sum);
      }
    } else f = ins_set_<use_set, (k + 1) % K>(x->ch[p[k] >= x->coord[k]], p, val);
    pushup(x);
    return f;
  }

  CEXP bool check_range(const_pointer x, cT_(point) L, cT_(point) R) CNE {
    flt_ (u32, i, 0, K)
      if (x->min[i] < L[i] || R[i] < x->max[i]) return false;
    return true;
  }
  CEXP bool check_point(const_pointer x, cT_(point) L, cT_(point) R) CNE {
    flt_ (u32, i, 0, K)
      if (x->coord[i] < L[i] || R[i] < x->coord[i]) return false;
    return true;
  }
  CEXP bool check(const_pointer x, cT_(point) L, cT_(point) R) CNE {
    if (!x) return false;
    flt_ (u32, i, 0, K)
      if (R[i] < x->min[i] || x->max[i] < L[i]) return false;
    return true;
  }
  CEXP void query_(const_pointer x, cT_(point) L, cT_(point) R, T& ans) CNE {
    if (!x) return;
    if (check_range(x, L, R)) {
      ans = op(ans, x->sum);
      return;
    }
    if (check_point(x, L, R)) ans = op(ans, x->val);
    if (check(x->ch[0], L, R)) query_(x->ch[0], L, R, ans);
    if (check(x->ch[1], L, R)) query_(x->ch[1], L, R, ans);
  }

 public:
  pointer root;

  // threshold = $O\left(\sqrt{n\log n}\right)$
  CEXPE KDtree(u32 rebuild_threshold, cT_(T) e = T{}) NE : E{e}, B{rebuild_threshold}, cnt{0}, root{nullptr} { assert(rebuild_threshold > 1); }
  CEXP ~KDtree() NE { dealloc_subtree(root, alloc); }

  CEXP void insert(cT_(point) coord, cT_(T) val) NE {
    if ((cnt += ins_set_<false, 0>(root, coord, val)) == B) cnt = 0, rebuild(root);
  }
  CEXP void set(cT_(point) coord, cT_(T) val) NE {
    if ((cnt += ins_set_<true, 0>(root, coord, val)) == B) cnt = 0, rebuild(root);
  }
  //! [L, R]
  CEXP T query(cT_(point) L, cT_(point) R) CNE {
    T ans{E};
    query_(root, L, R, ans);
    return ans;
  }

 private:
  alc<TIFA> alloc;
};

}  // namespace tifa_libs::ds

#endif