#ifndef TIFALIBS_DS_FHQ_TREAP_W
#define TIFALIBS_DS_FHQ_TREAP_W

#include "../rand/gen.hpp"

namespace tifa_libs::ds {

template <class T, auto op, auto e, class F, auto mapping, auto composition, auto id,
          bool reverse_ = false, bool recovery = false>
requires requires(T val, T val_l, T val_r, F tag, F tag_l, F tag_r) {
  { e() } -> std::same_as<T>;
  { id() } -> std::same_as<F>;
  { op(val_l, val_r) } -> std::same_as<T>;
  { mapping(tag, val) } -> std::same_as<T>;
  { composition(tag_l, tag_r) } -> std::same_as<F>;
}
class fhq_treap_w {
  //! initial cnt = 1;
  struct TIFA {
    T w, val;
    F sign;
    u32 sz;
    arr<u32, 2> son{};
    i32 rad;
    bool rev;
    CEXP TIFA(T W = e(), T VAL = e(), u32 SZ = 0, i32 RAD = 0, F SIGN = id()) : w(W), val(VAL), sign(SIGN), sz(SZ), rad(RAD), rev(0) {}
  };
  rand::Gen<i32> gen;
  vec<TIFA> t;
  vecu sta;
  u32 cnt;

  CEXP u32 newnode(T val) {
    u32 ret;
    if (sta.size()) ret = *sta.rbegin(), sta.pop_back(), t[ret] = TIFA(val, val, 1, gen());
    else ret = ++cnt, t[ret] = TIFA(val, val, 1, gen());
    return ret;
  }
  CEXP void rm(u32 u) { sta.push_back(u); }
  CEXP void update(u32 u) { t[u].w = op(t[t[u].son[0]].w, op(t[u].val, t[t[u].son[1]].w)), t[u].sz = t[t[u].son[0]].sz + t[t[u].son[1]].sz + 1; }
  CEXP void reverse__(u32 u) {
    static_assert(reverse_);
    swap(t[u].son[0], t[u].son[1]), t[u].rev ^= 1;
  }
  CEXP void all_update(u32 u, F f) {
    if (u) t[u].val = mapping(f, t[u].val), t[u].w = mapping(f, t[u].w), t[u].sign = composition(f, t[u].sign);
  }
  CEXP void pushdown(u32 u) {
    if (u) {
      all_update(t[u].son[0], t[u].sign), all_update(t[u].son[1], t[u].sign), t[u].sign = id();
      if CEXP (reverse_)
        if (t[u].rev) reverse__(t[u].son[0]), reverse__(t[u].son[1]), t[u].rev = 0;
    }
  }

 public:
  u32 root;

  CEXPE fhq_treap_w(u32 MAX_N) : gen(), t(MAX_N + 1), sta(), cnt(0), root(0) {
    if CEXP (recovery) sta.reserve(MAX_N + 1);
  }

  CEXP void split(u32 u, u32 k, u32& x, u32& y) {
    if (!u) x = y = 0;
    else if (pushdown(u); t[t[u].son[0]].sz < k) x = u, split(t[u].son[1], k - t[t[u].son[0]].sz - 1, t[x].son[1], y), update(x);
    else y = u, split(t[u].son[0], k, x, t[y].son[0]), update(y);
  }
  CEXP u32 merge(u32 x, u32 y) {
    pushdown(x), pushdown(y);
    if (x && y) {
      if (t[x].rad <= t[y].rad) return t[x].son[1] = merge(t[x].son[1], y), update(x), x;
      return t[y].son[0] = merge(x, t[y].son[0]), update(y), y;
    } else return x + y;
  }
  CEXP void insert(T w, u32 id_) {
    u32 x, y;
    split(root, id_, x, y), root = merge(merge(x, newnode(w)), y);
  }
  CEXP void insert(T w) { insert(w, cnt); }
  CEXP void erase(u32 id_) {
    u32 x, y, z;
    split(root, id_, x, y), split(y, 1, z, y);
    if CEXP (recovery) rm(z);
    root = merge(x, y);
  }
  CEXP void update(u32 l, u32 r, F f) {
    u32 x, y, z;
    split(root, r + 1, x, z), split(x, l, x, y), all_update(y, f), root = merge(merge(x, y), z);
  }
  CEXP void reverse(u32 l, u32 r) {
    static_assert(reverse_);
    u32 x, y, z;
    split(root, r + 1, x, z), split(x, l, x, y), reverse__(y), root = merge(merge(x, y), z);
  }
  CEXP T query(u32 l, u32 r) {
    u32 x, y, z;
    split(root, r + 1, x, z), split(x, l, x, y);
    T ret = t[y].w;
    return root = merge(merge(x, y), z), ret;
  }
};

}  // namespace tifa_libs::ds

#endif